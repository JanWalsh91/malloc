/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:53:29 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 17:42:33 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Returns the region list corresponding to allocation size request
*/

t_region	*get_first_region(size_t size)
{
	if (size <= TINY_LIMIT)
		return (&g_lists.tiny);
	if (size <= SMALL_LIMIT)
		return (&g_lists.small);
	return (&g_lists.large);
}

/*
** Returns the mininum map size depending on size to allocated
*/

size_t		get_region_min_map_size(size_t size)
{
	size_t	page_size;
	size_t	page_count;

	if (size <= TINY_LIMIT)
		return (TINY_MIN_MAP_SIZE);
	else if (size <= SMALL_LIMIT)
		return (SMALL_MIN_MAP_SIZE);
	else
	{
		page_size = getpagesize();
		page_count = (size + REGION_HEADER_SIZE) / page_size + 1;
		return (page_count * page_size);
	}
}

t_region	get_new_region(size_t size)
{
	t_region	region;
	size_t		final_size;

	region = NULL;
	size = size + BLOCK_HEADER_SIZE;
	if (size <= BLOCK_HEADER_SIZE)
		return (NULL);
	final_size = get_region_min_map_size(size);
	region = mmap(0, final_size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	if (region == MAP_FAILED)
	{
		print_mmap_error();
		errno = ENOMEM;
		return (NULL);
	}
	region->size = final_size;
	region->next = NULL;
	region->last_block = NULL;
	region->after_last_block = (t_block)(&region->content);
	region->content = 0;
	return (region);
}

int			region_has_space(t_region region, size_t size)
{
	if (get_size_of_free_space_at_end_of_region(region) >= size +
		BLOCK_HEADER_SIZE)
		return (1);
	else
		return (0);
}

t_region	get_region_head(size_t size)
{
	t_region	*head;

	head = get_first_region(size);
	if (!*head)
		*head = get_new_region(size);
	return (*head);
}
