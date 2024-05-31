/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 06:41:15 by ******           #+#    #+#             */
/*   Updated: 2024/05/30 14:20:12 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
The following is the grammar definition of minishell:

The starting symbol is *cmdlist*. The reason being
that it may contain pipe and thus also cmd.

tokens are: TWORD, TAND, TOR, TPIPE

cmdlist	->	pipe TAND pipe
		->	pipe TOR pipe
		->	pipe

pipe 	->	cmd TPIPE pipe
		->	cmd

cmd		->	TWORD args

args	->	TWORD args
		->	ϵ

redir	->	TGT TWORD
		->	TLT	TWORD
*/

#include "minishell.h"
#include <dirent.h>

int	is_pattern(char *s)
{
	while (*s)
	{
		if (*s == '*')
			return (1);
		s++;
	}
	return (0);
}

t_wlist	*wlist_from_pattern(char *ptn)
{
	t_wlist			*n;
	DIR				*d;
	struct dirent	*e;

	n = NULL;
	d = opendir(".");
	if (d == NULL)
	{
		perror("opendir failed");
		return (NULL);
	}
	while (1)
	{
		e = readdir(d);
		if (!e)
			break ;
		if (ft_strcmp(e->d_name, ".") == 0 || ft_strcmp(e->d_name, "..") == 0)
			continue ;
		if (pattern_match(ptn, e->d_name))
			wlist_add(&n, (t_word){ft_strdup(e->d_name), TWORD});
	}
	closedir(d);
	return (n);
}

t_ast	*parse(char *s)
{
	input_init_str(s);
	token(1);
	return (nt_cmdlist());
}

t_ast	*parse_error(void)
{
	ft_stderr("Error: Parse error\n");
	shell()->exit_status = 2;
	return (NULL);
}
