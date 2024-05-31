/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:45:37 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 13:38:18 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

/* Returns heredoc prefix for current minishell instance */
char	*heredoc_prefix(void)
{
	char	*tmp;
	char	*pref;

	tmp = ft_getpid();
	pref = ft_strjoin(HEREDOC_PREFIX, tmp);
	ft_free(tmp);
	tmp = ft_strjoin(pref, "_");
	ft_free(pref);
	return (tmp);
}

/* Generate unique temporary filename for heredoc */
char	*heredoc_filename(int id)
{
	char	*tmp;
	char	*pref;
	char	*fn;

	tmp = heredoc_prefix();
	pref = ft_strjoin(HEREDOC_DIR, heredoc_prefix());
	ft_free(tmp);
	tmp = ft_itoa(id);
	fn = ft_strjoin(pref, tmp);
	ft_free(pref);
	ft_free(tmp);
	return (fn);
}

/* Read one heredoc into `fd` until `d` is foudn */
void	heredoc_read(int fd, char *d)
{
	char	*delim;
	char	*line;

	delim = d;
	cont();
	while (1)
	{
		line = get_prompt();
		if (line == NULL)
		{
			ft_stderro((char *[]){NAME ": warning: here-document",
				" delimited by end-of-file\n", NULL});
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		ft_free(line);
	}
	nocont();
	ft_free(delim);
}

void	heredoc_clean(void)
{
	DIR				*d;
	struct dirent	*e;
	char			*pref;
	char			*tmp;

	pref = heredoc_prefix();
	d = opendir(HEREDOC_DIR);
	while (1)
	{
		e = readdir(d);
		if (!e)
			break ;
		if (ft_startswith(e->d_name, pref))
		{
			if (DEBUG)
				printf("Unlinking heredoc %s\n", e->d_name);
			tmp = ft_strjoin(HEREDOC_DIR, e->d_name);
			unlink(tmp);
			ft_free(tmp);
		}
	}
	ft_free(pref);
	closedir(d);
}

/* Read in all heredocs previously found in line */
void	shell_heredoc(t_shell *s)
{
	t_wlist	*hdoc;
	int		fd;
	char	*fname;

	hdoc = s->heredocs;
	while (hdoc)
	{
		fname = heredoc_filename(hdoc->word.flags);
		if (DEBUG)
			printf("Creating heredoc %s\n", fname);
		fd = open(fname, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		heredoc_read(fd, hdoc->word.word);
		ft_close(fd);
		ft_free(fname);
		wlist_remove(&hdoc, hdoc);
		s->heredoc_count--;
	}
	s->heredocs = NULL;
}
