/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:28:54 by ******            #+#    #+#             */
/*   Updated: 2024/05/28 22:46:06 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdarg.h>

/*

Those functions needs to be removed because of illegal va_functions

*/

/* Compare to var args */
int	wlist_eq(t_wlist *l, int num, ...)
{
	va_list	args;

	va_start(args, num);
	while (l && num--)
	{
		if (ft_strcmp(l->word.word, va_arg(args, char *)) != 0)
			return (va_end(args), 0);
		l = l->next;
	}
	va_end(args);
	return (!num && !l);
}

t_wlist	*wlist(int n, ...)
{
	t_wlist	*l;
	va_list	args;

	l = NULL;
	va_start(args, n);
	while (n--)
		wlist_adds(&l, va_arg(args, char *));
	va_end(args);
	return (l);
}
