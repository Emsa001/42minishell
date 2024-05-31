/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:22:48 by ******           #+#    #+#             */
/*   Updated: 2024/05/30 13:55:54 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Shell input handler

Supports lookbehind of 2 and also ungch twice

Usage:
input_init_str("test");
input_init_fd(0);

then use
- ch()
- gch(i)
- unch()
*/

static void	input_unget(char buffer[5], int unget)
{
	if (unget)
	{
		ft_memmove(buffer, buffer + 1, 4);
		buffer[4] = '\0';
	}
}

static void	initialize(char *init_input, int init_fd, char **input, int *fd)
{
	if (init_input || init_fd != -1)
	{
		*input = init_input;
		*fd = init_fd;
	}
}

static void	handle_input(char *buffer, char **input, int fd)
{
	if (input && *input)
		input_str(buffer, input);
	else if (isatty(fd) || FORCE_TTY)
		input_term(buffer, input);
	else if (fd >= 0)
		input_fd(buffer, fd);
	else
		buffer[2] = '\0';
}

static char	lookbehind(char *buffer, int pos)
{
	if (pos < 0)
		return (buffer[2 - pos]);
	return (buffer[2]);
}

char	getinput(char *init_input, int init_fd, int pos, int unget)
{
	static char	*input = NULL;
	static int	fd = -1;
	static char	buffer[5] = "\0\0\0\0";

	if (init_input || init_fd != -1)
	{
		initialize(init_input, init_fd, &input, &fd);
		ft_strncpy(buffer, "\0\0\0\0", 5);
		return ('\0');
	}
	input_unget(buffer, unget);
	if (pos > 0)
	{
		memmove(buffer + 1, buffer, 4);
		buffer[0] = '\0';
		if (buffer[2])
			return (buffer[2]);
		handle_input(buffer, &input, fd);
	}
	return (lookbehind(buffer, pos));
}
