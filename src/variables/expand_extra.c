/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:26:44 by ******            #+#    #+#             */
/*   Updated: 2024/05/25 14:32:38 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* internal expansion */
bool	exp_internal(t_vars *v)
{
	const char	c = v->word[v->i];
	const int	len = ft_strlen(v->word);
	char		*temp;

	temp = NULL;
	if (c == VARHOME)
	{
		temp = ft_strdup("~");
		if (len == 1)
			temp = ft_strdup(get_home());
	}
	else if (c == VARPID)
		temp = ft_getpid();
	else if (c == VARNAME)
		temp = ft_strdup(NAME);
	else if (c == VARSTATUS)
		temp = ft_itoa(get_exit_status());
	if (temp)
	{
		v->str = ft_strjoin(v->str, temp);
		v->i++;
		ft_free(temp);
		return (true);
	}
	return (false);
}

/* wildcard expansion */
void	exp_wildcard(t_wlist **lst)
{
	t_wlist	*l;
	t_wlist	*wln;
	t_wlist	*next;
	t_wlist	*prev;

	l = *lst;
	while (l)
	{
		if (is_pattern(l->word.word))
		{
			wln = wlist_from_pattern(l->word.word);
			if (wln)
			{
				next = l->next;
				prev = wlist_remove(lst, l);
				wlist_last(wln)->next = next;
				if (prev)
					prev->next = wln;
				else
					*lst = wln;
				l = wln;
			}
		}
		l = l->next;
	}
}
