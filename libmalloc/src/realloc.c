/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:33 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/05 13:43:00 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
	void	*ret;

	ret = NULL;
	pthread_mutex_lock(&g_mutex);
	init_lists();
	ret = realloc_thread_unsafe(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ret);
}

void		*realloc_thread_unsafe(void *ptr, size_t size)
{
	t_region	region;
	t_block		block;

	if (!ptr)
		return (malloc_thread_unsafe(size));
	if (size <= 0 || !(region = get_region_containing_pointer(ptr)) ||
		!(block = get_block_containing_pointer(region, ptr)))
		return (NULL);
	size = align16(size);
	if (size <= block->size)
	{
		if (can_split_block(block, size))
		{
			block->free = 0;
			split_block(region, block, size);
		}
		return (ptr);
	}
	if (!block->next && get_size_of_free_space_at_end_of_region(region) +
		block->size >= size)
	{
		block->size = size;
		return (get_block_content(block));
	}
	return (malloc_and_free(block, size, ptr));
}

void		*malloc_and_free(t_block block, size_t size, void *ptr)
{
	void	*new_ptr;

	new_ptr = malloc_thread_unsafe(size);
	if (new_ptr)
		memcpy(new_ptr, ptr, block->size);
	free_thread_unsafe(ptr);
	return (new_ptr);
}
