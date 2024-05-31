/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:32:41 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 15:46:02 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_newline(t_wlist **args)
{
	bool	newline;

	newline = true;
	while (*args && (*args)->word.word[0] == '-' && ft_isonly((*args)->word.word
			+ 1, 'n'))
	{
		newline = false;
		*args = (*args)->next;
	}
	return (newline);
}

int	util_echo(t_shell *shl, t_wlist *args)
{
	bool	newline;

	(void)shl;
	args = args->next;
	newline = is_newline(&args);
	while (args)
	{
		printf("%s", args->word.word);
		if (args->next)
			printf(" ");
		args = args->next;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
