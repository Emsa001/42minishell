/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:19:33 by ******            #+#    #+#             */
/*   Updated: 2024/05/22 19:45:31 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_addhistory(void)
{
	t_shell	*s;

	s = shell();
	if (s->input_str == NULL || s->input_str[0] == '\0')
		return ;
	s->input_str[ft_strlen(s->input_str) - 1] = '\0';
	add_history(s->input_str);
	ft_free(shell()->input_str);
	shell()->input_str = ft_strdup("");
}

void	ft_addinput(char *str)
{
	char	*temp;

	if (ft_strlen(str) == 1 && inccont(0) == 0)
		return ;
	temp = ft_strdup(shell()->input_str);
	ft_free(shell()->input_str);
	shell()->input_str = ft_strjoin(temp, str);
	ft_free(temp);
}
