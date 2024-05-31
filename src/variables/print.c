/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:49:58 by ******            #+#    #+#             */
/*   Updated: 2024/05/29 12:02:33 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define EXPORT_PREFIX "declare -x "

void	print_env(void)
{
	t_env	*current;

	current = shell()->l_envp;
	while (current != NULL)
	{
		if (current->value != NULL && current->value[0] != '\0')
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

static t_env	*insert_sorted(t_env *head, const char *key, const char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = (t_env *)ft_malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->value = NULL;
	if (value != NULL)
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!head || ft_strcmp(key, head->key) < 0)
	{
		new_node->next = head;
		return (new_node);
	}
	current = head;
	while (current->next && ft_strcmp(key, current->next->key) > 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
	return (head);
}

t_env	*exported_vars(t_env *envp)
{
	t_env	*exported;
	t_env	*current;

	exported = NULL;
	current = envp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, "_") != 0)
			exported = insert_sorted(exported, current->key, current->value);
		current = current->next;
	}
	return (exported);
}

void	print_export(void)
{
	t_env	*exported;
	t_env	*temp;

	exported = exported_vars(shell()->l_envp);
	while (exported != NULL)
	{
		temp = exported;
		if (exported->value != NULL)
			printf("%s%s=\"%s\"\n", EXPORT_PREFIX, exported->key,
				exported->value);
		else
			printf("%s%s\n", EXPORT_PREFIX, exported->key);
		exported = exported->next;
		ft_free(temp->key);
		ft_free(temp->value);
		ft_free(temp);
	}
}
