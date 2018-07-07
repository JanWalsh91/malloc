/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:33 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/07 16:51:35 by jwalsh           ###   ########.fr       */
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
	// ft_putstr("realloc_thread_unsafe\n");
	t_region	region;
	t_block		block;

	if (!ptr) {
		// ft_putstr("realloc_thread_unsafe A END\n");
		return (malloc_thread_unsafe(size));
	}
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
		// ft_putstr("realloc_thread_unsafe A END\n");
		return (ptr);
	}
	if (!block->next && get_size_of_free_space_at_end_of_region(region) +
		block->size >= size)
	{
		block->size = size;
		// ft_putstr("realloc_thread_unsafe B END\n");
		update_last_block_info(region, block);
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
	// ft_putstr("realloc_thread_unsafe C END\n");
	return (new_ptr);
}
