/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:33:30 by ******            #+#    #+#             */
/*   Updated: 2024/05/21 12:52:56 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define USAGE "export: usage: export [name[=value] ...]\n"

int	export_var(t_shell *shl, char *var)
{
	char	*name;
	char	*value;

	(void) shl;
	name = ft_strdup(var);
	if (ft_strchr(var, '='))
		name[ft_strchr(var, '=') - var] = '\0';
	value = NULL;
	if (ft_strchr(var, '='))
		value = ft_strdup(ft_strchr(var, '=') + 1);
	if (!get_var(name))
		return (add_var(name, value));
	else if (value)
		return (update_var(name, value), SUCCESS);
	return (SUCCESS);
}

int	util_export(t_shell *shl, t_wlist *args)
{
	int	ret;

	ret = SUCCESS;
	if (invalid_option(args, USAGE))
		return (MISUSED);
	if (wlist_len(args) == 1)
		return (print_export(), SUCCESS);
	args = args->next;
	while (args != NULL)
	{
		if (export_var(shl, args->word.word) == FAILED)
			ret = FAILED;
		args = args->next;
	}
	return (ret);
}
