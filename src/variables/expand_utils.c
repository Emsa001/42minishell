/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:04:11 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 16:02:47 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	*exp_init(char *word)
{
	t_vars	*v;

	v = ft_calloc(1, sizeof(t_vars));
	v->i = 0;
	v->word = word;
	v->str = ft_strdup("");
	v->varname = ft_strdup("");
	v->temp = ft_strdup("");
	v->is_var = false;
	v->is_quote = false;
	return (v);
}

bool	var_start(t_vars *v)
{
	if (v->word[v->i] == VARSTART)
	{
		v->varname = ft_strdup("");
		v->is_var = true;
		v->i++;
		if (v->word[v->i] == VARQUOTE)
		{
			v->is_quote = true;
			v->i++;
		}
		return (true);
	}
	return (false);
}

void	handle_var_value(t_vars *v, t_wlist **new_words, char **value)
{
	int		k;
	int		last;
	char	*to_add;

	k = 0;
	last = ft_arrlen(value) - 1;
	while (value[k])
	{
		if (k == last && v->word[v->i + 1] != '\0')
			v->str = ft_strjoin(v->str, value[k]);
		else
		{
			to_add = ft_strjoin(v->str, value[k]);
			wlist_addl(new_words, to_add, v->current->word.flags);
			v->str = ft_strdup("");
		}
		k++;
	}
}

bool	var_end(t_vars *v, t_wlist **new_words)
{
	char	**value;

	if (v->word[v->i] == VAREND)
	{
		value = ft_splitset(get_varform(v->varname), FT_WHITESPACE);
		if (!v->is_quote && ft_arrlen(value) > 1)
			handle_var_value(v, new_words, value);
		else
			v->str = ft_strjoin(v->str, get_varform(v->varname));
		v->is_var = false;
		v->is_quote = false;
		v->i++;
		ft_arrdel((void **)value);
		return (true);
	}
	return (false);
}
