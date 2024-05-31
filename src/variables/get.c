/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:23:19 by ******            #+#    #+#             */
/*   Updated: 2024/05/29 11:42:30 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_var(char *key)
{
	t_env	*current;

	current = shell()->l_envp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

char	*get_varval(char *key)
{
	const t_env	*var = get_var(key);

	if (var && var->value)
		return (var->value);
	return (NULL);
}

char	*get_varform(char *str)
{
	char	*var;

	var = get_varval(str);
	if (!var)
		return ("");
	return (var);
}

char	*get_home(void)
{
	if (get_varval("HOME") == NULL)
		return (shell()->home);
	return (get_varform("HOME"));
}

char	*ft_getpid(void)
{
	int		fd;
	char	*file;
	char	**split;
	char	*pid;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return ("42");
	file = get_next_line(fd);
	if (file == NULL)
	{
		ft_close(fd);
		return ("42");
	}
	split = ft_split(file, ' ');
	ft_close(fd);
	pid = ft_strdup(split[0]);
	ft_arrdel((void **)split);
	return (pid);
}
