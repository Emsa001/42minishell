/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:33:38 by ******            #+#    #+#             */
/*   Updated: 2024/05/21 16:01:41 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_option_valid(char *str)
{
	int	i;

	if (!str)
		return (false);
	if (str[0] != '-')
		return (true);
	i = 1;
	while (str[i])
	{
		if (str[i] != '-')
			return (false);
		if (i >= 2)
			return (false);
		i++;
	}
	return (true);
}

bool	invalid_option(t_wlist *args, char *usage)

{
	char	*c;

	if (args->next && !is_option_valid(args->next->word.word))
	{
		c = args->next->word.word + 1;
		c[1] = '\0';
		ft_stderro((char *[]){NAME ": ", args->word.word,
			": invalid option -- '", c, "'\n", usage, NULL});
		return (true);
	}
	return (false);
}
