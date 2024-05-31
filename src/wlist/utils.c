/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:27:20 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 10:18:29 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Get length */
size_t	wlist_len(t_wlist *l)
{
	size_t	len;

	len = 0;
	while (l)
	{
		len++;
		l = l->next;
	}
	return (len);
}

/* Convert string array */
char	**wlist_to_strarr(t_wlist *l)
{
	char			**arr;
	size_t			len;
	unsigned int	i;

	len = wlist_len(l);
	arr = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (i < len)
	{
		arr[i++] = ft_strdup(l->word.word);
		l = l->next;
	}
	return (arr);
}

/* Print wlist, one word per line */
void	wlist_print(t_wlist *l)
{
	while (l)
	{
		printf("|%s| (%d)", l->word.word, l->word.flags);
		l = l->next;
		if (l)
			printf("\n");
	}
	printf("\n");
}

/* Get last element */
t_wlist	*wlist_last(t_wlist *l)
{
	while (l && l->next)
		l = l->next;
	return (l);
}

int	wlist_cmp(t_wlist *a, t_wlist *b)
{
	int	diff;

	while (a && b)
	{
		diff = ft_strcmp(a->word.word, a->word.word);
		if (diff)
			return (diff);
		a = a->next;
		b = b->next;
	}
	if (a)
		return (1);
	else if (b)
		return (-1);
	return (0);
}
