/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:24:04 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 14:20:22 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_wlist	*wlist_new(t_word word)
{
	t_wlist	*l;

	l = ft_malloc(sizeof(t_wlist));
	l->word = word;
	l->next = NULL;
	return (l);
}

/* Add word to word list */
void	wlist_add(t_wlist **l, t_word w)
{
	t_wlist	*last;
	t_wlist	*lnew;

	last = NULL;
	if (*l)
		last = wlist_last(*l);
	lnew = wlist_new(w);
	if (last)
		last->next = lnew;
	else
		*l = lnew;
}

/* Add a copy of `s` */
void	wlist_adds(t_wlist **l, char *s)
{
	wlist_add(l, (t_word){ft_strdup(s), 0});
}

void	wlist_addl(t_wlist **lst, char *s, int flags)
{
	wlist_add(lst, (t_word){ft_strdup(s), flags});
}
