/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 01:47:36 by ******           #+#    #+#             */
/*   Updated: 2024/05/16 15:10:53 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

/* Execute list */
int	ast_list_exec(t_ast *n, t_shell *shell)
{
	int	retcode1;
	int	retcode2;

	if (DEBUG)
		printf("  executing list\n");
	retcode1 = ast_exec(n->data.tree.left, shell);
	if (retcode1 > 0 && n->data.tree.op == TAND)
		return (retcode1);
	if (retcode1 == 0 && n->data.tree.op == TOR)
		return (retcode1);
	retcode2 = ast_exec(n->data.tree.right, shell);
	return (retcode2);
}

/* Execute AST of any type
Return exit code */
int	ast_exec(t_ast *n, t_shell *shell)
{
	pid_t	pid;
	int		s;

	if (!n)
		return (-1);
	if (n->type == CMD)
	{
		ast_expand(n);
		s = cmd_exec(&n->data.cmd, &pid, 0);
		if (s == PENDING)
			s = cmd_wait(pid, 1);
		set_exit_status(s);
		return (s);
	}
	else if (n->data.tree.op == TPIPE)
	{
		s = ast_pipe_exec(n, shell);
		set_exit_status(s);
		return (s);
	}
	else if (n->data.tree.op == TAND || n->data.tree.op == TOR)
		return (ast_list_exec(n, shell));
	return (-1);
}

void	ast_del(t_ast *n)
{
	if (!n)
		return ;
	if (n->type == CMD)
	{
		wlist_del(n->data.cmd.words);
		ft_free(n);
	}
	else if (n->type == TREE)
	{
		if (n->data.tree.left)
			ast_del(n->data.tree.left);
		if (n->data.tree.right)
			ast_del(n->data.tree.right);
		ft_free(n);
	}
	else
		printf("FATAL ast_del\n");
}
