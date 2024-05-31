/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:25:53 by ******            #+#    #+#             */
/*   Updated: 2024/05/27 15:30:51 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Remove from wlist `lst` item `item`, return node before it */
t_wlist	*wlist_remove(t_wlist **lst, t_wlist *item)
{
	t_wlist	*prev;
	t_wlist	*l;

	l = *lst;
	prev = NULL;
	while (l)
	{
		if (l == item)
		{
			if (prev)
				prev->next = l->next;
			else
				*lst = l->next;
			ft_free(item);
			return (prev);
		}
		prev = l;
		l = l->next;
	}
	return (NULL);
}

/* destroy word list */
void	wlist_del(t_wlist *l)
{
	t_wlist	*next;

	while (l)
	{
		next = l->next;
		ft_free(l);
		l = next;
	}
}
