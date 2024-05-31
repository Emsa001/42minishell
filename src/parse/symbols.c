/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:30:31 by ******           #+#    #+#             */
/*   Updated: 2024/05/30 11:49:48 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nt_command_word(t_ast *n, t_word *word_new, int *valid)
{
	if (accept_redir())
	{
		if (accept(TDLESS))
			word_new->word = heredoc_filename(shell()->heredoc_count);
		word_new->flags = token(0).flags;
		token(1);
	}
	else
		word_new->flags = TWORD;
	if (accept(TWORD))
	{
		*valid = 1;
		if (word_new->flags != TDLESS)
			word_new->word = token(0).word;
		else
		{
			wlist_add(&shell()->heredocs,
				(t_word){token(0).word, shell()->heredoc_count});
			shell()->heredoc_count++;
		}
		wlist_add(&n->data.cmd.words, *word_new);
		token(1);
		return (0);
	}
	return (-1);
}

t_ast	*nt_command(void)
{
	t_ast	*n;
	t_word	word_new;
	int		valid;

	valid = 0;
	if (!accept(TWORD) && !accept(TGREAT) && !accept(TLESS) && !accept(TDGREAT)
		&& !accept(TDLESS))
		return (NULL);
	n = ast_cmd_new();
	while (1)
	{
		word_new = (t_word){NULL, 0};
		if (nt_command_word(n, &word_new, &valid) < 0)
			break ;
	}
	if (!valid)
		return (ast_del(n), NULL);
	return (n);
}

t_ast	*nt_pipe(void)
{
	t_ast	*p;
	t_ast	*n;

	p = nt_command();
	if (!p)
		return (NULL);
	if (accept(TPIPE))
	{
		cont();
		n = ast_tree_new(token(0).flags);
		token(1);
		while (accept(TNEWLINE))
			token(1);
		nocont();
		n->data.tree.left = p;
		n->data.tree.right = nt_pipe();
		if (!n->data.tree.right)
			return (ast_del(p), NULL);
		p = n;
	}
	return (p);
}

t_ast	*nt_cmdlist(void)
{
	t_ast	*cl;
	t_ast	*n;

	if (accept(TNEWLINE))
		return (NULL);
	cl = nt_pipe();
	if (!cl)
		return (parse_error());
	while (accept(TAND) || accept(TOR))
	{
		cont();
		n = ast_tree_new(token(0).flags);
		token(1);
		while (accept(TNEWLINE))
			token(1);
		nocont();
		n->data.tree.left = cl;
		n->data.tree.right = nt_pipe();
		if (!n->data.tree.right)
			return (ast_del(cl), parse_error());
		cl = n;
	}
	if (!cl || !accept(TNEWLINE))
		return (ast_del(cl), parse_error());
	return (cl);
}
