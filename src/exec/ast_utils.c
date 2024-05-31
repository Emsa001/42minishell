/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:53:45 by ******            #+#    #+#             */
/*   Updated: 2024/05/26 17:25:34 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Create new ast tree with operator `op` */
t_ast	*ast_tree_new(t_token op)
{
	t_ast	*node;

	node = ft_malloc(sizeof(t_ast));
	node->type = TREE;
	node->data.tree.op = op;
	node->data.tree.left = NULL;
	node->data.tree.right = NULL;
	return (node);
}

/* Create new ast command */
t_ast	*ast_cmd_new(void)
{
	t_ast	*node;

	node = ft_malloc(sizeof(t_ast));
	node->type = CMD;
	node->data.cmd.words = NULL;
	node->data.cmd.input[0] = -1;
	node->data.cmd.input[1] = -1;
	node->data.cmd.output[0] = -1;
	node->data.cmd.output[1] = -1;
	node->data.cmd.flags = 0;
	return (node);
}

/* Count length of pipe and return it */
// every valid AST node has pipelen of at least 1
int	ast_pipelen(t_ast *p)
{
	int	len;

	if (!p)
		return (0);
	len = 1;
	while (p->type == TREE && p->data.tree.op == TPIPE)
	{
		len++;
		p = p->data.tree.right;
	}
	return (len);
}
