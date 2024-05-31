/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:03:09 by ******           #+#    #+#             */
/*   Updated: 2024/05/30 12:02:00 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ast_pipe_exec_elem(t_ast *p, int i, t_pipeinfo *pi)
{
	t_cmd	*cmd;

	if (p->type == CMD)
		cmd = &p->data.cmd;
	else if (p->type == TREE)
		cmd = &p->data.tree.left->data.cmd;
	if (i < pi->len - 1 && pipe(&pi->pipes[2 * i]) < 0)
		return (perror("pipe"), 1);
	if (pi->len > 1 && i > 0)
		ft_memcpy(cmd->input, &pi->pipes[2 * (i - 1)], sizeof(int) * 2);
	if (pi->len > 1 && i < pi->len - 1)
		ft_memcpy(cmd->output, &pi->pipes[2 * i], sizeof(int) * 2);
	cmd_exec(cmd, &pi->pids[i], 1);
	if (i > 0)
		ft_close(pi->pipes[2 * (i - 1)]);
	if (i < pi->len - 1)
		ft_close(pi->pipes[2 * i + 1]);
	return (0);
}

int	ast_pipe_await(t_pipeinfo *pi)
{
	int	i;
	int	ecode;

	i = 0;
	while (i < pi->len)
	{
		if (pi->pids[i] >= 0)
			ecode = cmd_wait(pi->pids[i], i == pi->len - 1);
		i++;
	}
	return (ecode);
}

int	ast_pipe_exec(t_ast *p, t_shell *shell)
{
	t_pipeinfo	pipeinfo;
	int			ecode;
	int			i;
	int			res;

	ast_expand(p);
	(void) shell;
	ecode = 0;
	pipeinfo.len = ast_pipelen(p);
	pipeinfo.pids = ft_malloc(sizeof(pid_t) * pipeinfo.len);
	pipeinfo.pipes = ft_malloc(sizeof(int) * 2 * (pipeinfo.len - 1));
	if (DEBUG)
		printf("executing pipe of length %i\n", pipeinfo.len);
	i = 0;
	while (i < pipeinfo.len)
	{
		res = ast_pipe_exec_elem(p, i++, &pipeinfo);
		if (res > 0)
			return (res);
		if (p->type == TREE)
			p = p->data.tree.right;
	}
	ecode = ast_pipe_await(&pipeinfo);
	return (ecode);
}
