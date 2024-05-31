/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hostname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:34:16 by ******            #+#    #+#             */
/*   Updated: 2024/05/29 11:42:30 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_hostname(void)
{
	int		file;
	char	*hostname;
	char	*newline;
	char	*dot;

	hostname = NULL;
	file = open("/etc/hostname", O_RDONLY);
	if (file < 0)
		return (ft_strdup("hostname"));
	hostname = get_next_line(file);
	if (!hostname)
	{
		ft_close(file);
		return (ft_strdup("hostname"));
	}
	newline = ft_strchr(hostname, '\n');
	dot = ft_strchr(hostname, '.');
	if (newline)
		*newline = '\0';
	if (dot)
		*dot = '\0';
	ft_close(file);
	return (hostname);
}
