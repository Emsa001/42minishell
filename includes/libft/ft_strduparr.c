/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strduparr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:17:33 by ******            #+#    #+#             */
/*   Updated: 2024/05/21 14:22:32 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_clean_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_strduparr(const char **src)
{
	int		size;
	char	**new_arr;
	int		i;

	size = 0;
	while (src[size] != NULL)
	{
		size++;
	}
	new_arr = malloc((size + 1) * sizeof(char *));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_arr[i] = ft_strdup(src[i]);
		if (!new_arr[i])
		{
			ft_clean_arr(new_arr);
			return (NULL);
		}
		i++;
	}
	new_arr[size] = NULL;
	return (new_arr);
}
