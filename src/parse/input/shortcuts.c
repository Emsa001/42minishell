/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcuts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:20:30 by ******            #+#    #+#             */
/*   Updated: 2024/05/23 17:59:46 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	gch(int i)
{
	return (getinput(NULL, -1, i, 0));
}

char	ch(void)
{
	return (gch(0));
}

void	ungch(void)
{
	getinput(NULL, -1, 0, 1);
}

void	input_init_fd(int fd)
{
	getinput(NULL, fd, 0, 0);
}

void	input_init_str(char *s)
{
	getinput(s, -1, 0, 0);
}
