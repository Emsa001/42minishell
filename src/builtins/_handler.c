/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _handler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:12:28 by ******            #+#    #+#             */
/*   Updated: 2024/05/30 17:25:49 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	util_test(t_shell *shl, t_wlist *args)
{
	(void) shl;
	printf("Hello from test builtin!\n");
	wlist_print(args);
	return (42);
}

/* Return function pointer to builtin function corresponding to name `s` */
t_builtin	builtin_find(char *s)
{
	int						i;
	const t_builtin_mapping	builtins[] = {\
		{"testbuiltin", util_test}, \
		{"cd", util_cd}, \
		{"echo", util_echo}, \
		{"env", util_env}, \
		{"exit", util_exit}, \
		{"export", util_export}, \
		{"pwd", util_pwd}, \
		{"unset", util_unset}, \
		{"", NULL} \
	};

	if (!s)
		return (NULL);
	i = 0;
	while (builtins[i].fun)
	{
		if (ft_strcmp(builtins[i].name, s) == 0)
			return (builtins[i].fun);
		i++;
	}
	return (NULL);
}
