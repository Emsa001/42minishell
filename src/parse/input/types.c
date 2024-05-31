/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:22:48 by ******           #+#    #+#             */
/*   Updated: 2024/05/30 16:28:44 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* If we're reading a string and it hasn't ended and has started
go on to the next */
void	input_str(char *buffer, char **input)
{
	buffer[2] = **input;
	if (**input)
		(*input)++;
	else
		*input = NULL;
}

// buffer exhausted and end of input but cont
void	input_term(char *buffer, char **input)
{
	char	*rl;

	set_signals_interactive();
	rl = get_prompt();
	if (rl == NULL)
		ft_exit(SUCCESS);
	ft_free(*input);
	*input = ft_strjoin(rl, "\n");
	ft_addinput(*input);
	ft_free(rl);
	input_str(buffer, input);
	set_signals_noninteractive();
}

int	input_fd(char *buffer, int fd)
{
	static char	filebuffer[64];
	static int	bufpos = 64;
	static int	readres = 0;

	if (bufpos >= 64 || readres <= 0 || bufpos > readres)
	{
		readres = read(fd, filebuffer, 64);
		if (readres == -1)
		{
			perror("read error");
			buffer[2] = '\0';
			return (-1);
		}
		bufpos = 0;
	}
	if (readres > 0 && bufpos < readres)
		buffer[2] = filebuffer[bufpos];
	else
		buffer[2] = '\0';
	bufpos++;
	return (readres);
}
