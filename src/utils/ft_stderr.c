/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stderr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:44:44 by ******            #+#    #+#             */
/*   Updated: 2024/05/21 15:59:05 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_stderr(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
}

void	ft_stderro(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
		ft_putstr_fd(arg[i++], STDERR_FILENO);
}
