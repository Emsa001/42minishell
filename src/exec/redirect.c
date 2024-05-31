/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:17:08 by ******           #+#    #+#             */
/*   Updated: 2024/05/30 10:16:35 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <errno.h>

int	redirect_input(t_cmd *cmd, t_wlist *cur, int *remove)
{
	int	oflags;

	if (cur->word.flags == TGREAT || cur->word.flags == TDGREAT)
	{
		if (cmd->output[1] >= 0)
			ft_close(cmd->output[1]);
		oflags = O_WRONLY | O_CREAT | O_TRUNC;
		if (cur->word.flags == TDGREAT)
			oflags = O_WRONLY | O_CREAT | O_APPEND;
		cmd->output[1] = open(cur->word.word, oflags, 0644);
		if (cmd->output[1] < 0)
		{
			ft_stderro((char *[]){NAME ": ", cur->word.word, ": ",
				strerror(errno), "\n", NULL});
			return (FAILED);
		}
		*remove = 1;
	}
	return (SUCCESS);
}

int	redirect_output(t_cmd *cmd, t_wlist *cur, int *remove)
{
	if (cur->word.flags == TLESS || cur->word.flags == TDLESS)
	{
		if (cmd->input[0] >= 0)
			ft_close(cmd->input[1]);
		cmd->input[0] = open(cur->word.word, O_RDONLY);
		if (cmd->input[0] < 0)
		{
			ft_stderro((char *[]){NAME ": ", cur->word.word, ": ",
				strerror(errno), "\n", NULL});
			return (FAILED);
		}
		*remove = 1;
	}
	return (SUCCESS);
}

int	redirect(t_cmd *cmd)
{
	t_wlist	*cur;
	t_wlist	*next;
	int		remove;

	cur = cmd->words;
	while (cur)
	{
		remove = 0;
		if (redirect_input(cmd, cur, &remove) != SUCCESS || \
				redirect_output(cmd, cur, &remove) != SUCCESS)
			return (FAILED);
		next = cur->next;
		if (remove)
			wlist_remove(&cmd->words, cur);
		cur = next;
	}
	if (cmd->input[0] >= 0)
		dup2(cmd->input[0], STDIN_FILENO);
	if (cmd->output[1] >= 0)
		dup2(cmd->output[1], STDOUT_FILENO);
	return (SUCCESS);
}

void	redirect_restore(t_shell *shl, t_cmd *cmd)
{
	if (cmd->input[0] > 2)
		ft_close(cmd->input[0]);
	if (cmd->output[1] > 2)
		ft_close(cmd->output[1]);
	dup2(shl->stdin_dup, STDIN_FILENO);
	dup2(shl->stdout_dup, STDOUT_FILENO);
}
