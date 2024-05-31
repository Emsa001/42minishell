/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:00:15 by ******           #+#    #+#             */
/*   Updated: 2024/01/12 14:00:17 by ******          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_max(int a, int b)
{
	return (ft_max_int(a, b));
}

int	ft_max_int(int a, int b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

float	ft_max_float(float a, float b)
{
	if (a < b)
		return (b);
	else
		return (a);
}
