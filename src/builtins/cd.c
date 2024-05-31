/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:32:18 by ******            #+#    #+#             */
/*   Updated: 2024/05/27 17:36:00 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define USAGE		"cd: usage: cd [dir]\n"
#define NOTSETOLD	": cd: OLDPWD not set\n"
#define NOTSETHOME	": cd: HOME not set\n"

static void	update_dirs(t_shell *shell)
{
	char	*temp;

	temp = getcwd(NULL, 0);
	if (!temp)
	{
		perror("getcwd");
		return ;
	}
	ft_addalloc(temp);
	update_var("OLDPWD", shell->current_dir);
	update_var("PWD", temp);
	ft_free(shell->current_dir);
	shell->current_dir = ft_strdup(temp);
	ft_free(temp);
}

static int	check_args(t_wlist *args)
{
	if (invalid_option(args, USAGE))
		return (MISUSED);
	if (wlist_len(args) > 2)
		return (ft_stderr(NAME ": cd: too many arguments\n"), FAILED);
	return (SUCCESS);
}

static int	update_current(t_wlist **args)
{
	const char	*home = get_varval("HOME");
	const char	*oldpwd = get_varval("OLDPWD");

	if (!(*args) || ft_strcmp((*args)->word.word, "--") == 0)
	{
		if (!home)
			return (printf(NAME " " NOTSETHOME), FAILED);
		if (!(*args))
			return (wlist_adds(args, (char *) home), SUCCESS);
		wlist_replace(*args, (char *) home);
	}
	else if (ft_strcmp((*args)->word.word, "-") == 0)
	{
		if (!oldpwd)
			return (printf(NAME " " NOTSETOLD), FAILED);
		wlist_replace(*args, (char *) oldpwd);
	}
	return (SUCCESS);
}

int	util_cd(t_shell *shl, t_wlist *args)
{
	const int	check = check_args(args);

	args = args->next;
	if (check != SUCCESS)
		return (check);
	if (update_current(&args) == FAILED)
		return (FAILED);
	if (chdir(args->word.word) == -1)
	{
		ft_stderr(NAME ": cd: ");
		perror(args->word.word);
		return (FAILED);
	}
	update_dirs(shl);
	return (SUCCESS);
}
