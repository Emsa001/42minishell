/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:48:04 by ******           #+#    #+#             */
/*   Updated: 2024/05/30 16:11:43 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 1. If the end of input is recognized, the current token (if any) shall be
delimited. */
void	tok_input_end(t_tokstate *t)
{
	if (t->rule_applied)
		return ;
	if (!ch())
	{
		t->rule_applied = 1;
		t->delimit = 1;
	}
}

/* 2. If the previous character was used as part of an operator and the
current character is not quoted and can be used with the previous characters
to form an operator, it shall be used as part of that (operator) token. */
void	tok_operator_append(t_tokstate *t)
{
	if (t->rule_applied || !(t->flags == TOP && !t->quote))
		return ;
	if (gch(-1) == '|' && ch() == '|')
		t->flags = TOR;
	else if (gch(-1) == '&' && ch() == '&')
		t->flags = TAND;
	else if (gch(-1) == '<' && ch() == '<')
		t->flags = TDLESS;
	else if (gch(-1) == '>' && ch() == '>')
		t->flags = TDGREAT;
	else
		return ;
	errset(buffer_feed(&t->ctoken, ch()));
	t->rule_applied = 1;
	t->delimit = 1;
}

/* 3. If the previous character was used as part of an operator and the
current character cannot be used with the previous characters to form an
operator, the operator containing the previous character shall be delimited. */
void	tok_operator_split(t_tokstate *t)
{
	if (t->rule_applied)
		return ;
	if (t->flags == TOP && ((gch(-1) == '|' && ch() != '|') || \
			(gch(-1) == '&' && ch() != '&') || \
			(gch(-1) == '<' && ch() != '<') || \
			(gch(-1) == '>' && ch() != '>')))
	{
		if (gch(-1) == '|')
			t->flags = TPIPE;
		else if (gch(-1) == '&')
			t->flags = TSAND;
		else if (gch(-1) == '<')
			t->flags = TLESS;
		else if (gch(-1) == '>')
			t->flags = TGREAT;
		else
		{
			errset(buffer_feed(&t->ctoken, ch()));
			t->flags = TWORD;
		}
		ungch();
		t->delimit = 1;
		t->rule_applied = 1;
	}
}

static void	tok_quoting_varend(t_tokstate *t)
{
	if (t->is_variable)
	{
		errset(buffer_feed(&t->ctoken, VAREND));
		t->is_variable = false;
	}
}

/* 4. If the current character is <backslash>, single-quote, or double-quote
and it is not quoted, it shall affect quoting for subsequent characters up to
the end of the quoted text. */
void	tok_quoting(t_tokstate *t)
{
	if (t->rule_applied)
		return ;
	if (t->quote == ch())
	{
		tok_quoting_varend(t);
		nocont();
		t->quote = 0;
	}
	else if (!t->quote && (ch() == '\'' || ch() == '"'))
	{
		t->flags = TWORD;
		tok_quoting_varend(t);
		cont();
		t->quote = ch();
	}
	else
		return ;
	t->rule_applied = 1;
}
