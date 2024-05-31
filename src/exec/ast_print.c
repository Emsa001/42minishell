/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:51:57 by ******            #+#    #+#             */
/*   Updated: 2024/05/29 17:15:54 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	indent(int i)
{
	while (i-- > 0)
		printf("  ");
}

void	ast_print_lvl_tree(t_ast *a, int lvl)
{
	indent(lvl);
	if (a->data.tree.op == TPIPE)
		printf("->pipe\n");
	else if (a->data.tree.op == TAND)
		printf("->and\n");
	else if (a->data.tree.op == TOR)
		printf("->or\n");
	else
		printf("op: %i\n", a->data.tree.op);
	if (a->data.tree.left)
		ast_print_lvl(a->data.tree.left, lvl + 1);
	if (a->data.tree.right)
		ast_print_lvl(a->data.tree.right, lvl + 1);
}

void	ast_print_lvl(t_ast *a, int lvl)
{
	if (!a)
	{
		indent(lvl);
		printf("NULL\n");
		return ;
	}
	if (a->type == TREE)
	{
		ast_print_lvl_tree(a, lvl);
	}
	else if (a->type == CMD)
	{
		indent(lvl);
		printf("%s\n", a->data.cmd.words->word.word);
	}
	else
		printf("FATAL ast_print_lvl\n");
}

/* Print overview of AST */
void	ast_print(t_ast *a)
{
	printf("=== ast ===\n");
	ast_print_lvl(a, 0);
	printf("\n\n");
}
