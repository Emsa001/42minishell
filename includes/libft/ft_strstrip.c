/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 08:50:45 by ******           #+#    #+#             */
/*   Updated: 2024/05/30 10:20:00 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcount(const char *s, const char *set)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (ft_charinset(*s, set))
			count++;
		s++;
	}
	return (count);
}

char	*ft_strstrip(const char *s, const char *set)
{
	char	*res;
	char	*res_orig;

	if (!s)
		return (NULL);
	res = malloc((ft_strlen(s) - ft_strcount(s, set) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res_orig = res;
	while (*s)
	{
		if (!ft_charinset(*s, set))
			*res++ = *s;
		s++;
	}
	*res = '\0';
	return (res_orig);
}

void	ft_strstrip_char(const char *s, const char c)
{
	char	*res;

	res = ft_strchr(s, c);
	if (res)
		*res = '\0';
}
