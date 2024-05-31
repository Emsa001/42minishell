/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:33:49 by ******            #+#    #+#             */
/*   Updated: 2024/05/23 13:36:20 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_var(char *key, char *value, t_env **head)
{
	t_env	*new_node;
	t_env	*current;

	if (get_var(key) != NULL)
		return ;
	new_node = (t_env *)ft_malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	if (value == NULL)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

int	add_var(char *key, char *value)
{
	if (!verify_var_name(key))
	{
		ft_stderro((char *[]){NAME " export: `", key, "=", NULL});
		if (value)
			ft_stderro((char *[]){value, NULL});
		ft_stderro((char *[]){"': not a valid identifier\n", NULL});
		return (FAILED);
	}
	init_var(key, value, &shell()->l_envp);
	return (SUCCESS);
}

void	update_var(char *key, char *value)
{
	t_env	*current;

	current = shell()->l_envp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			ft_free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}
