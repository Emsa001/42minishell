/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 18:18:35 by ******           #+#    #+#             */
/*   Updated: 2024/05/30 17:31:27 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* Runs argument in new env, assigning pid of new process */
int	run_env(char *cmd, t_wlist *argv)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == -1)
	{
		ft_stderro((char *[]){NAME ": ", cmd, ": ",
			"No such file or directory\n", NULL});
		return (NOT_FOUND);
	}
	if (access(cmd, X_OK) != 0)
	{
		ft_stderro((char *[]){NAME ": ", cmd, ": ",
			"Permission denied\n", NULL});
		return (PERM_DENIED);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_stderro((char *[]){NAME ": ", cmd, ": ", "Is a directory\n", NULL});
		return (PERM_DENIED);
	}
	execve(cmd, wlist_to_strarr(argv), lenvp_to_strarr(shell()->l_envp));
	ft_stderro((char *[]){NAME, ": ", cmd, ": Unknown Error\n", NULL});
	exit(EXIT_FAILURE);
}

/* Join together paths `p1` and `p2`, ensuring they are connected by
exactly one slash '/'

Example: ft_pathjoin("/bin", "echo") -> "/bin/echo" */
char	*ft_pathjoin(char *p1, char *p2)
{
	bool	p1_slash;
	bool	p2_slash;
	char	*pn;
	char	*res;

	if (!p1 || !p2)
		return (NULL);
	p1_slash = ft_endswith(p1, "/");
	p2_slash = ft_startswith(p2, "/");
	if (!p1_slash && !p2_slash)
	{
		pn = ft_strjoin(p1, "/");
		if (!pn)
			return (NULL);
		res = ft_strjoin(pn, p2);
		ft_free(pn);
		return (res);
	}
	if (p1_slash && p2_slash)
		p2++;
	return (ft_strjoin(p1, p2));
}

char	*cmd_locate(char *cmdstr)
{
	char	**path;
	char	*fpath;

	path = ft_split(get_varform("PATH"), ':');
	while (*path)
	{
		fpath = ft_pathjoin(*path, cmdstr);
		if (access(fpath, F_OK) == 0)
		{
			if (DEBUG)
				printf("  %10s found here: %s\n", cmdstr, fpath);
			return (ft_arrdel((void **) path), fpath);
		}
		ft_free(fpath);
		path++;
	}
	ft_arrdel((void **) path);
	return (NULL);
}

void	cmd_print(t_ast *n)
{
	t_cmd	*cmd;

	cmd = &n->data.cmd;
	printf("===command===\n");
	printf("$ %s\n", cmd->words->word.word);
	printf("args: ");
	wlist_print(cmd->words->next);
	printf("\n");
}
