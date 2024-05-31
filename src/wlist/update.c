/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:26:21 by ******            #+#    #+#             */
/*   Updated: 2024/05/22 18:30:12 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* update word */
void	wlist_update(t_wlist *l, char *s)
{
	ft_free(l->word.word);
	l->word.word = ft_strdup(s);
}

void	wlist_replace(t_wlist *l, char *s)
{
	ft_free(l->word.word);
	l->word.word = s;
}
