/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:48:38 by ******           #+#    #+#             */
/*   Updated: 2024/05/23 18:31:11 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 5. If the current character is an unquoted '$' or '`', the shell shall
identify the start of any candidates for parameter expansion  */

static bool	tok_varinternal_end(t_tokstate *t)
{
	if (t->is_variable == true && !is_varchar(ch()))
	{
		t->is_variable = false;
		errset(buffer_feed(&t->ctoken, VAREND));
	}
	if (ch() == '~' && t->quote == 0)
	{
		t->rule_applied = 1;
		t->flags = TWORD;
		errset(buffer_feed(&t->ctoken, VARHOME));
		return (true);
	}
	return (false);
}

static void	tok_varinternal_feed(t_tokstate *t)
{
	char	n;

	n = gch(1);
	if (n == '?')
	{
		errset(buffer_feed(&t->ctoken, VARSTATUS));
		t->rule_applied = 1;
		t->flags = TWORD;
	}
	else if (n == '$')
	{
		errset(buffer_feed(&t->ctoken, VARPID));
		t->rule_applied = 1;
		t->flags = TWORD;
	}
	else if (n == '0')
	{
		errset(buffer_feed(&t->ctoken, VARNAME));
		t->rule_applied = 1;
		t->flags = TWORD;
	}
	else
		ungch();
}

void	tok_varinternal(t_tokstate *t)
{
	if (t->rule_applied)
		return ;
	if (tok_varinternal_end(t))
		return ;
	else if (ch() == '$' && t->quote != '\'')
		tok_varinternal_feed(t);
}

void	tok_variables(t_tokstate *t)
{
	char	n;

	if (t->rule_applied)
		return ;
	if (t->is_variable == true && !is_varchar(ch()))
	{
		t->is_variable = false;
		errset(buffer_feed(&t->ctoken, VAREND));
	}
	if (ch() == '$' && t->quote != '\'')
	{
		n = gch(1);
		if (is_param(n) || (ft_isinset(n, "\'\"") && t->quote == 0))
		{
			ungch();
			errset(buffer_feed(&t->ctoken, VARSTART));
			if (t->quote != 0)
				errset(buffer_feed(&t->ctoken, VARQUOTE));
			t->is_variable = true;
			t->rule_applied = 1;
			t->flags = TWORD;
		}
		else
			ungch();
	}
}
