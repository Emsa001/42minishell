/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 10:51:54 by ******            #+#    #+#             */
/*   Updated: 2024/05/27 16:57:02 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_ps2(void)
{
	if (get_var("PS2"))
		return (ft_strdup(get_varval("PS2")));
	return (ft_strdup("> "));
}

static char	*set_default_ps1(void)
{
	char	*cwd;
	char	*temp;
	char	*exit_status;
	char	*prompt;

	cwd = getcwd_converted(shell());
	temp = ft_strdup(BLUE_500);
	if (get_exit_status() != 0 && get_exit_status() != 130)
	{
		exit_status = get_exit_status_str();
		temp = ft_strappend(RED_500 "(" RED, exit_status);
		temp = ft_strappend(temp, RED_500 ") " BLUE_500);
	}
	temp = ft_strappend(temp, shell()->username);
	temp = ft_strappend(temp, YELLOW_600 "@" RED_500);
	temp = ft_strappend(temp, shell()->hostname);
	temp = ft_strappend(temp, YELLOW_600 ":" GREEN_700);
	temp = ft_strappend(temp, cwd);
	prompt = ft_strjoin(temp, YELLOW_600 "$ " RESET);
	ft_free(cwd);
	ft_free(temp);
	return (prompt);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*rl;

	if (inccont(0))
		prompt = get_ps2();
	else if (!get_varval("PS1"))
		prompt = set_default_ps1();
	else
		prompt = ft_strdup(get_varval("PS1"));
	rl = readline(prompt);
	ft_addalloc(rl);
	ft_free(prompt);
	return (rl);
}
