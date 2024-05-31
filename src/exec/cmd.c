/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:26:00 by ******           #+#    #+#             */
/*   Updated: 2024/05/30 17:54:09 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

void	cmd_exec_inner(t_execinfo *einfo)
{
	if (einfo->builtin)
		einfo->s = einfo->builtin(shell(), einfo->cmd->words);
	else if (!ft_strchr(einfo->cmdstr, '/'))
	{
		if (einfo->prog)
			einfo->s = run_env(einfo->prog, einfo->cmd->words);
		else
		{
			ft_stderro((char *[]){einfo->cmdstr,
				": command not found\n", NULL});
			einfo->s = NOT_FOUND;
		}
	}
	else
		einfo->s = run_env(einfo->cmdstr, einfo->cmd->words);
	if (*einfo->pid == 0)
		exit(einfo->s);
}

void	cmd_exec_redirect(t_execinfo *einfo)
{
	if (redirect(einfo->cmd))
	{
		if (*einfo->pid == 0)
			exit(FAILED);
		einfo->s = FAILED;
		redirect_restore(shell(), einfo->cmd);
		return ;
	}
	if (!einfo->cmd->words)
	{
		if (*einfo->pid == 0)
			exit(SUCCESS);
		einfo->s = SUCCESS;
		redirect_restore(shell(), einfo->cmd);
		return ;
	}
	cmd_exec_inner(einfo);
	redirect_restore(shell(), einfo->cmd);
}

static char	*cmd_get_cmdstr(t_cmd *cmd)
{
	t_wlist	*w;

	w = cmd->words;
	while (w)
	{
		if (w->word.flags == TWORD)
			return (w->word.word);
		w = w->next;
	}
	return (NULL);
}

/* See https://pubs.opengroup.org
/onlinepubs/9699919799.2016edition/utilities/V3_chap02.html#tag_18_09_01_01

If fork is true, the command will always run in its own process,
even if it's a builtin */
int	cmd_exec(t_cmd *cmd, pid_t *pid, int newenv)
{
	t_execinfo	einfo;

	if (!cmd->words)
		return (SUCCESS);
	einfo = (t_execinfo){NULL, cmd, NULL, NULL, newenv, -1, pid};
	einfo.cmdstr = cmd_get_cmdstr(cmd);
	if (!einfo.cmdstr)
		einfo.cmdstr = ft_strdup("");
	einfo.builtin = builtin_find(einfo.cmdstr);
	einfo.prog = cmd_locate(einfo.cmdstr);
	*einfo.pid = -1;
	if ((!einfo.builtin && einfo.prog) || einfo.newenv || \
		ft_strchr(einfo.cmdstr, '/'))
	{
		*einfo.pid = fork();
		if (*einfo.pid < 0)
			return (42);
		if (*einfo.pid > 0)
			return (PENDING);
		shell()->interactive = 0;
		ft_close(einfo.cmd->output[0]);
	}
	cmd_exec_redirect(&einfo);
	return (einfo.s);
}

int	cmd_wait(pid_t pid, int last)
{
	int	wstatus;
	int	ecode;

	ecode = 0;
	wstatus = 0;
	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		ecode = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
		ecode = SIGNALED + WTERMSIG(wstatus);
	if (WIFSTOPPED(wstatus))
		ecode = SIGNALED + WSTOPSIG(wstatus);
	if (ecode >= SIGNALED && last)
		printf("\n");
	return (ecode);
}
