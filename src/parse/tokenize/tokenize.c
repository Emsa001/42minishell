/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:28:55 by ******           #+#    #+#             */
/*   Updated: 2024/05/30 16:12:15 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tok_loop(t_tokstate *t)
{
	while (gch(1) || inccont(0) > 0)
	{
		t->rule_applied = 0;
		tok_input_end(t);
		tok_operator_append(t);
		tok_operator_split(t);
		tok_quoting(t);
		tok_varinternal(t);
		tok_variables(t);
		tok_operator_new(t);
		tok_blank(t);
		tok_word_append(t);
		tok_comment(t);
		tok_word_new(t);
		if (t->delimit)
			break ;
	}
}

static void	tok_init(t_tokstate *t)
{
	t->ctoken = NULL;
	t->flags = TNONE;
	t->delimit = 0;
	t->rule_applied = 0;
	t->is_variable = 0;
	if (t->flags_next)
	{
		t->flags = t->flags_next;
		t->flags_next = 0;
	}
	if (t->flags == TNEWLINE)
	{
		t->delimit = 1;
		t->rule_applied = 1;
	}
}

/*
See "2.3 Token recognition"
https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html

Returns t_word struct, where flags is TERR on error
*/
t_word	next_token(void)
{
	static t_tokstate	t = (t_tokstate){NULL, {"\0\0"}, 0, NULL, 0, 0, '\0', 0,
		NULL, 0};
	char				*tmp;

	tok_init(&t);
	if (t.flags == TOP)
		errset(buffer_feed(&t.ctoken, ch()));
	if (t.flags == TNEWLINE)
		return ((t_word){.word = NULL, .flags = TNEWLINE});
	tok_loop(&t);
	tmp = buffer_to_str(t.ctoken);
	if (errset(0) != 0)
		t.flags = TERR;
	if (t.flags == TNONE)
		return ((t_word){
			.word = NULL,
			.flags = TNONE,
		});
	return ((t_word){
		.word = tmp,
		.flags = t.flags,
	});
}

t_word	ntoken(void)
{
	return (token(1));
}
