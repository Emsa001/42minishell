/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:33:20 by ******            #+#    #+#             */
/*   Updated: 2024/05/24 19:41:17 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define USAGE "pwd: usage: pwd\n"

int	util_pwd(t_shell *shl, t_wlist *args)
{
	if (invalid_option(args, USAGE))
		return (MISUSED);
	args = args->next;
	printf("%s\n", shl->current_dir);
	return (SUCCESS);
}
