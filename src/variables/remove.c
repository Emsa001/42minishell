/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:34:09 by ******            #+#    #+#             */
/*   Updated: 2024/05/22 13:25:05 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_var(char *key)
{
	t_env	*current;
	t_env	*prev;

	if (shell()->l_envp == NULL)
		return ;
	current = shell()->l_envp;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				shell()->l_envp = current->next;
			else
				prev->next = current->next;
			ft_free(current->key);
			ft_free(current->value);
			ft_free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
