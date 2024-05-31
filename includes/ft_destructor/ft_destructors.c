/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destructors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ****** <******@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:12:49 by ******            #+#    #+#             */
/*   Updated: 2024/05/22 18:33:43 by ******           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "ft_alloc.h"

static void	tryfree(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	ft_frees(void **ptr)
{
	while (*ptr != NULL)
	{
		ft_free(*ptr);
		ptr++;
	}
}

void	ft_free(void *ptr)
{
	t_allocs	*lst;
	t_allocs	*tmp;

	if (ptr == NULL)
		return ;
	lst = ft_allocs(NULL);
	tmp = NULL;
	while (lst != NULL)
	{
		if (lst->ptr == ptr)
		{
			tmp->next = lst->next;
			tryfree(lst->ptr);
			tryfree(lst);
			return ;
		}
		tmp = lst;
		lst = lst->next;
	}
}

void	ft_destructor(void)
{
	t_allocs	*lst;
	t_allocs	*temp;

	lst = ft_allocs(NULL);
	if (DEBUG_ALLOCS)
		printf("Passing %d allocations to destructor\n", ft_allocsize());
	while (lst != NULL)
	{
		temp = lst;
		lst = lst->next;
		if (temp->ptr != NULL)
		{
			tryfree(temp->ptr);
			temp->ptr = NULL;
		}
		tryfree(temp);
	}
	tryfree(lst);
}
