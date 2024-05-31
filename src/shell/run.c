/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:44:12 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 13:37:21 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_run(void)
{
	t_ast	*cl;

	while (1)
	{
		input_init_fd(shell()->input_fd);
		ft_addhistory();
		token(1);
		cl = nt_cmdlist();
		if (cl)
		{
			shell_heredoc(shell());
			if (DEBUG)
				ast_print(cl);
			ast_exec(cl, shell());
			ast_del(cl);
			heredoc_clean();
			if (token(0).flags == TNONE)
				break ;
		}
	}
}
