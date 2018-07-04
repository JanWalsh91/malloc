/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region_manager4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:53:29 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 17:43:26 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		unmap_region(t_region region)
{
	t_region	prev;
	t_region	next;

	prev = region->prev;
	next = region->next;
	munmap(region, region->size);
	if (prev)
		prev->next = next;
}

t_region	get_region_containing_pointer(void *ptr)
{
	t_region	lists[3];
	t_region	region;
	int			i;

	lists[0] = g_lists.tiny;
	lists[1] = g_lists.small;
	lists[2] = g_lists.large;
	i = -1;
	while (++i < 3)
		if (lists[i])
		{
			region = lists[i];
			while (region)
			{
				if ((size_t)region < (size_t)ptr &&
					(size_t)ptr < (size_t)((char *)region + region->size))
					return (region);
				region = region->next;
			}
		}
	return (NULL);
}
