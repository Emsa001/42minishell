/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:47:27 by ******            #+#    #+#             */
/*   Updated: 2024/05/27 15:47:44 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	paths_match(char **home_path, char **cwd_path)
{
	size_t	i;

	i = 0;
	while (home_path[i] && cwd_path[i])
	{
		if (ft_strcmp(home_path[i], cwd_path[i]) != 0)
			return (0);
		i++;
	}
	return (home_path[i] == NULL);
}

static char	*replace_varhome(char *cwd, const char *home_value)
{
	char	*temp;

	temp = ft_strjoin("~", cwd + ft_strlen(home_value));
	ft_free(cwd);
	return (temp);
}

char	*getcwd_converted(t_shell *shell)
{
	char		*cwd;
	const t_env	*home = get_var("HOME");
	char		**home_path;
	char		**cwd_path;

	home_path = NULL;
	cwd_path = NULL;
	cwd = ft_strdup(shell->current_dir);
	if (home && home->value)
	{
		home_path = ft_split(home->value, '/');
		cwd_path = ft_split(cwd, '/');
		if (!home_path || !cwd_path)
		{
			ft_arrsdel((char **[]){home_path, cwd_path, NULL});
			return (cwd);
		}
		if (paths_match(home_path, cwd_path) && ft_strncmp(cwd, home->value,
				ft_strlen(home->value)) == 0)
			cwd = replace_varhome(cwd, home->value);
		ft_arrsdel((char **[]){home_path, cwd_path, NULL});
	}
	return (cwd);
}
