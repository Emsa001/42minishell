/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:32:50 by ******            #+#    #+#             */
/*   Updated: 2024/05/29 12:02:25 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define USAGE "env: usage: env\n"

int	util_env(t_shell *shl, t_wlist *args)
{
	(void) shl;
	if (args->next && ft_strcmp(args->next->word.word, "-") == 0)
		return (SUCCESS);
	if (invalid_option(args, USAGE))
		return (MISUSED);
	return (print_env(), SUCCESS);
}
