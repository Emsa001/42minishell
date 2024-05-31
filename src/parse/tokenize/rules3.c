/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 18:12:29 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 15:34:33 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 6. If the current character is not quoted and can be used as the first
character of a new operator, the current token (if any) shall be delimited.
The current character shall be used as the beginning of the next (operator)
token. */
void	tok_operator_new(t_tokstate *t)
{
	t_token	tt;

	if (t->rule_applied)
		return ;
	if (!t->quote && (ch() == '|' || ch() == '&' || ch() == '<' || ch() == '>'
			|| ch() == '\n'))
	{
		t->rule_applied = 1;
		tt = TOP;
		if (ch() == '\n')
		{
			tt = TNEWLINE;
			t->delimit = 1;
		}
		if (t->ctoken)
		{
			t->delimit = 1;
			t->flags_next = tt;
			return ;
		}
		t->flags = tt;
	}
}

/* 7. If the current character is an unquoted <blank>, any token containing
the previous character is delimited and the current character shall be
discarded. */
void	tok_blank(t_tokstate *t)
{
	if (t->rule_applied)
		return ;
	if (!t->quote && (ft_isinset(ch(), FT_WHITESPACE) || ch() == '\n'))
	{
		t->rule_applied = 1;
		if (t->flags != TNONE)
		{
			t->delimit = 1;
		}
	}
}

/* 8. If the previous character was part of a word, the current character shall
be appended to that word. */
void	tok_word_append(t_tokstate *t)
{
	if (t->rule_applied)
		return ;
	if (t->flags == TWORD)
	{
		t->rule_applied = 1;
		errset(buffer_feed(&t->ctoken, ch()));
	}
}

/* 9. If the current character is a '#', it and all subsequent characters up to,
but excluding, the next <newline> shall be discarded as a comment.
The <newline> that ends the line is not considered part of the comment. */
void	tok_comment(t_tokstate *t)
{
	if (t->rule_applied)
		return ;
	if (ch() == '#')
	{
		t->rule_applied = 1;
		while (ch() && ch() != '\n')
			gch(1);
		ungch();
	}
}

/* 10. The current character is used as the start of a new word. */
void	tok_word_new(t_tokstate *t)
{
	if (t->rule_applied)
		return ;
	t->rule_applied = 1;
	errset(buffer_feed(&t->ctoken, ch()));
	t->flags = TWORD;
}
