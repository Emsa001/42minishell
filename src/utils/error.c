/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 13:20:09 by ******            #+#    #+#             */
/*   Updated: 2024/05/21 15:59:30 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	errset(int s)
{
	static int	status = 0;

	if (s != 0)
		status = s;
	return (status);
}

/*  WE DONT USE THOSE */

// void	ft_error(char *str)
// {
// 	perror(str);
// 	exit(EXIT_FAILURE);
// }
// void	errguard(t_shell *s, int status)
// {
// 	static t_shell	*shell = NULL;

// 	if (s)
// 		shell = s;
// 	if (status < 0)
// 	{
// 		shell_destroy(shell);
// 		exit(1);
// 	}
// }

// void	err(int status)
// {
// 	errguard(NULL, status);
// }
