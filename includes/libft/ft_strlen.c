/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:06:38 by ******           #+#    #+#             */
/*   Updated: 2023/11/17 11:54:08 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// size_t	ft_strnlen(const char *s, size_t n)
// {
// 	size_t	len;

// 	len = 0;
// 	while (s[len] != '\0' && len < n)
// 		len++;
// 	return (len);
// }

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}
