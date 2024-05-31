/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:42:15 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 16:39:32 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_errexit(void)
{
	shell_destroy(shell());
	exit(EXIT_FAILURE);
}

void	shell_destroy(t_shell *shl)
{
	if (!shl)
		return ;
	heredoc_clean();
	close(shl->stdin_dup);
	close(shl->stdout_dup);
	if (!shl->interactive)
		ft_close(shl->input_fd);
	env_del(shl->l_envp);
	ft_free(shl->current_dir);
	ft_free(shl);
	ft_destructor();
}
