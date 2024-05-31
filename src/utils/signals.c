/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:26:26 by ******            #+#    #+#             */
/*   Updated: 2024/05/27 16:56:41 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_reset_prompt(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	shell()->exit_status = 130;
}

void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

void	signal_set_on_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_replace_line("", 0);
}

/* set_signals_interactive:
	Sets the behavior in response to SIGINT (ctrl-c) and SIGQUIT (ctrl-\).
	SIGINT resets the user input prompt to a new blank line.
	SIGQUIT is ignored.
*/
void	set_signals_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

/* set_signals_noninteractive:
	Sets the behavior in response to SIGINT (ctrl -c) and SIGQUIT (ctrl -\).
	Used when minishell is in noninteractive mode, meaning it is not awaiting
	user input. For example, when a command is running (i.e. cat), minishell
*/
void	set_signals_noninteractive(void)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_flags = SA_RESTART;
	act.sa_handler = &signal_set_on_newline;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
