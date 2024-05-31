/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:15:11 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 16:47:02 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(int status)
{
	if (shell()->interactive)
		printf("exit\n");
	shell_destroy(shell());
	exit(status % 256);
}

static bool	is_valid_arg(char *s)
{
	long long unsigned int	val;
	int						i;

	val = 0;
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		val = val * 10 + (s[i] - '0');
		if (val > __LONG_MAX__)
			return (false);
		i++;
	}
	return (true);
}

int	util_exit(t_shell *shl, t_wlist *args)
{
	(void)shl;
	args = args->next;
	if (args && is_valid_arg(args->word.word) && args->next)
	{
		ft_stderr("minishell: exit: too many arguments\n");
		return (1);
	}
	if (args == NULL)
		ft_exit(SUCCESS);
	else if (!is_valid_arg(args->word.word))
	{
		ft_stderro((char *[]){NAME ": exit: ", args->word.word,
			": numeric argument required\n", NULL});
		ft_exit(MISUSED);
	}
	else
		ft_exit(ft_atoi(args->word.word));
	return (SUCCESS);
}
