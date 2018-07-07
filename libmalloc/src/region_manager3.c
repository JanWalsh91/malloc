/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region_manager3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:53:29 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/07 16:50:06 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		link_regions(t_region prev, t_region current)
{
	if (prev)
		prev->next = current;
	if (current)
		current->prev = prev;
}

int			region_is_free(t_region region)
{
	t_block block;

	block = (t_block)&region->content;
	while (block)
	{
		if (!block->free)
			return (0);
		block = block->next;
	}
	return (1);
}

int			try_to_unmap_regions(t_region region)
{
	int	nb_free_regions;
	int	nb_used_regions;

	nb_free_regions = 0;
	nb_used_regions = 0;
	while (region)
	{
		if (region_is_free(region))
		{
			++nb_free_regions;
			if (nb_free_regions >= 2)
			{
				unmap_region(region);
				return (1);
			}
		}
		else
			++nb_used_regions;
		if (region->next)
			region = region->next;
		else
			break ;
	}
	return (0);
}

void		unmap_all_regions(t_region region)
{
	while (region && region->prev)
		region = region->prev;
	unmap_regions_recursively(region);
	if (region == g_lists.tiny)
		g_lists.tiny = NULL;
	else if (region == g_lists.small)
		g_lists.small = NULL;
	else if (region == g_lists.large)
		g_lists.large = NULL;
}

void		unmap_regions_recursively(t_region region)
{
	if (region && region->next)
		unmap_regions_recursively(region->next);
	unmap_region(region);
}
