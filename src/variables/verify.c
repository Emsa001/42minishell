/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:09:43 by ******            #+#    #+#             */
/*   Updated: 2024/05/21 19:49:26 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_varstart(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_varchar(char c)
{
	return (is_varstart(c) || ft_isalnum(c));
}

bool	is_param(char c)
{
	return (is_varstart(c) || c == '?');
}

bool	verify_var_name(char *env_var)
{
	if (!is_varstart(env_var[0]))
		return (false);
	env_var++;
	while (*env_var)
	{
		if (!is_varchar(*env_var) && !ft_isdigit(*env_var))
			return (false);
		env_var++;
	}
	return (true);
}
