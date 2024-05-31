/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:34:40 by ******            #+#    #+#             */
/*   Updated: 2024/05/22 13:25:09 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define USAGE "unset: usage: unset [name ...]\n"

int	util_unset(t_shell *shl, t_wlist *args)
{
	(void)shl;
	if (invalid_option(args, USAGE))
		return (MISUSED);
	args = args->next;
	while (args)
	{
		if (verify_var_name(args->word.word))
			remove_var(args->word.word);
		args = args->next;
	}
	return (SUCCESS);
}
