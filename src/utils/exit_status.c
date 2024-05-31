/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:55:18 by ******            #+#    #+#             */
/*   Updated: 2024/05/27 16:57:38 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_exit_status(int value)
{
	shell()->exit_status = (value % 256);
}

int	get_exit_status(void)
{
	return (shell()->exit_status);
}

char	*get_exit_status_str(void)
{
	return (ft_itoa(shell()->exit_status));
}
