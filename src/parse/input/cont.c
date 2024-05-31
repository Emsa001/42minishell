/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:22:48 by ******           #+#    #+#             */
/*   Updated: 2024/05/29 12:08:35 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Retrieve continuation counter or add `inc` to it */
int	inccont(int inc)
{
	static int	contcount = 0;

	contcount += inc;
	return (contcount);
}

/* Increase continuation counter */
void	cont(void)
{
	inccont(1);
}

/* Decrease continuation counter */
void	nocont(void)
{
	inccont(-1);
}
