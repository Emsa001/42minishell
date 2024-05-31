/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:08:30 by ******            #+#    #+#             */
/*   Updated: 2024/05/22 18:33:37 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "ft_alloc.h"

void	ft_addalloc(void *ptr)
{
	t_allocs	*allocs;

	allocs = ft_allocs(NULL);
	if (FT_DESTRUCTOR)
		add_allocnode(&allocs, create_alloc(ptr));
}

void	*ft_malloc(size_t size)
{
	t_allocs	*allocs;
	void		*ptr;

	allocs = ft_allocs(NULL);
	if (allocs == NULL)
		return (malloc(size));
	ptr = malloc(size);
	if (ptr == NULL)
	{
		printf("Memory allocation failed\n");
		ft_destructor();
		exit(EXIT_FAILURE);
	}
	ft_addalloc(ptr);
	return (ptr);
}

static void	ft_bzeroo(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		*ptr++ = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzeroo(ptr, count * size);
	return (ptr);
}
