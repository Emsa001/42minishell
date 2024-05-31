/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:24:02 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 12:46:52 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_var(char **envp, t_env **head, int i)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	int		key_len;

	equal_sign = ft_strchr(envp[i], '=');
	if (equal_sign != NULL)
	{
		key_len = equal_sign - envp[i];
		key = (char *)ft_malloc(key_len + 1);
		ft_strncpy(key, envp[i], key_len);
		key[key_len] = '\0';
		value = ft_strdup(equal_sign + 1);
		init_var(key, value, head);
		ft_free(key);
		ft_free(value);
	}
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*head;

	i = 0;
	head = NULL;
	if (!envp)
		return (NULL);
	while (envp[i] != NULL)
		insert_var(envp, &head, i++);
	return (head);
}

void	env_del(t_env *l_envp)
{
	t_env	*next;

	if (!l_envp)
		return ;
	while (l_envp)
	{
		ft_free(l_envp->key);
		ft_free(l_envp->value);
		next = l_envp->next;
		ft_free(l_envp);
		l_envp = next;
	}
}

char	**lenvpstr(t_env *l_envp)
{
	int		len;
	t_env	*current;
	char	**envp;

	len = 0;
	current = l_envp;
	while (current != NULL)
	{
		current = current->next;
		len++;
	}
	envp = (char **)ft_malloc(sizeof(char *) * (len + 1));
	return (envp);
}

char	**lenvp_to_strarr(t_env *l_envp)
{
	char	**envp;
	t_env	*current;
	int		i;
	char	*temp;

	envp = lenvpstr(l_envp);
	current = l_envp;
	i = 0;
	while (current != NULL)
	{
		temp = ft_strjoin(current->key, "=");
		if (current->value != NULL)
			envp[i] = ft_strjoin(temp, current->value);
		else
			envp[i] = temp;
		i++;
		current = current->next;
	}
	envp[i] = NULL;
	return (envp);
}
