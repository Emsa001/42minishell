/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:37:42 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 16:35:48 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Pseudo singleton t_shell. Initialize once with arguments,
	then use with NULL arguments. */

static void	shell_init_envp(t_shell *s, char **envp)
{
	char	*pwd;

	s->envp = envp;
	s->l_envp = init_env(envp);
	if (getenv("PS1"))
		remove_var("PS1");
	if (getenv("PS2"))
		remove_var("PS2");
	if (getenv("SHLVL") == NULL)
		init_var("SHLVL", "0", &s->l_envp);
	if (getenv("PWD") == NULL)
	{
		pwd = getcwd(NULL, 0);
		ft_addalloc(pwd);
		init_var("PWD", pwd, &s->l_envp);
		ft_free(pwd);
	}
	if (getenv("OLDPWD") == NULL)
		init_var("OLDPWD", NULL, &s->l_envp);
}

static void	shell_init_settings(t_shell *s)
{
	s->current_dir = getcwd(NULL, 0);
	ft_addalloc(s->current_dir);
	s->home = ft_strdup(get_varform("HOME"));
	s->exit_status = 0;
	s->interactive = isatty(STDIN_FILENO) || FORCE_TTY;
	s->heredocs = NULL;
	s->heredoc_count = 0;
	s->stdin_dup = dup(STDIN_FILENO);
	s->stdout_dup = dup(STDOUT_FILENO);
	s->input_str = ft_strdup("");
	if (get_var("LOGNAME"))
		s->username = ft_strdup(get_varform("LOGNAME"));
	else
		s->username = NAME;
	s->hostname = get_hostname();
}

static void	shell_set_lvl(void)
{
	t_env	*shlvl;
	int		shlvl_int;
	char	*shlvl_str;

	shlvl = get_var("SHLVL");
	shlvl_int = 1;
	if (shlvl)
		shlvl_int += ft_atoi(shlvl->value);
	if (shlvl_int < 0)
		shlvl_int = 0;
	if (shlvl_int >= MAX_SHLVL)
	{
		printf(NAME ": warning: shell level (%d) too high, resetting to 1\n",
			shlvl_int);
		shlvl_int = 1;
	}
	shlvl_str = ft_itoa(shlvl_int);
	update_var("SHLVL", shlvl_str);
	ft_free(shlvl_str);
}

t_shell	*shell_init(int argc, char **argv, char **envp)
{
	static t_shell	*s = NULL;

	if (s)
		return (s);
	ft_alloc_init();
	s = ft_malloc(sizeof(t_shell));
	if (!s)
	{
		ft_stderro((char *[]){"Fatal: malloc failed", NULL});
		shell_errexit();
	}
	ft_bzero(s, sizeof(t_shell));
	if (argc > 1)
	{
		s->input_fd = open(argv[1], O_RDONLY);
		s->interactive = isatty(STDIN_FILENO) || FORCE_TTY;
	}
	shell_init_envp(s, envp);
	shell_init_settings(s);
	shell_set_lvl();
	return (s);
}

t_shell	*shell(void)
{
	return (shell_init(0, NULL, NULL));
}
