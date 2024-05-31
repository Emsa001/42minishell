/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:58:17 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 16:04:10 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exp_variablee(t_vars *v, t_wlist **new_words)
{
	while (v->word[v->i])
	{
		if (exp_internal(v) || var_start(v) || var_end(v, new_words))
			continue ;
		if (v->is_var)
			ft_addchar(&v->varname, v->word[v->i]);
		else
			ft_addchar(&v->str, v->word[v->i]);
		v->i++;
	}
}

/* Function to expand variables in a word list */
void	exp_variable(t_wlist **lst)
{
	t_wlist	*current;
	t_wlist	*new_words_head;
	t_wlist	**new_words;
	t_vars	*v;

	current = *lst;
	new_words_head = NULL;
	new_words = &new_words_head;
	while (current)
	{
		v = exp_init(current->word.word);
		v->current = current;
		exp_variablee(v, new_words);
		if (v->str[0] != '\0' || v->current->word.word[0] == '\0')
			wlist_addl(new_words, v->str, current->word.flags);
		ft_frees((void *[]){v->str, v->varname, v->temp, v, NULL});
		current = current->next;
	}
	wlist_del(*lst);
	*lst = new_words_head;
}

/* Perform expansions */
void	ast_expand(t_ast *a)
{
	if (a->type == CMD)
	{
		exp_variable(&a->data.cmd.words);
		exp_wildcard(&a->data.cmd.words);
	}
	else if (a->type == TREE)
	{
		if (a->data.tree.left)
			ast_expand(a->data.tree.left);
		if (a->data.tree.right)
			ast_expand(a->data.tree.right);
	}
}
