/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:39 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/05 14:06:58 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	init_lists();
	free_thread_unsafe(ptr);
	pthread_mutex_unlock(&g_mutex);
}

void		free_thread_unsafe(void *ptr)
{
	t_region	region;
	t_block		block;

	if (!ptr)
		return ;
	region = get_region_containing_pointer(ptr);
	if (!region)
		return ;
	block = get_block_containing_pointer(region, ptr);
	if (!block)
		return ;
	block->free = 1;
	defragment(region, block);
	while (region->prev)
		region = region->prev;
	try_to_unmap_regions(region);
	scribble(block, 0x5);
}

void		defragment(t_region region, t_block block)
{
	if (!block->free)
		return ;
	if (block->next && block->next->free)
		merge_blocks(region, block, block->next);
	if (block->prev && block->prev->free)
	{
		merge_blocks(region, block->prev, block);
		block = block->prev;
	}
	if (!block->next)
		unset_block(region, block);
}

void		merge_blocks(t_region region, t_block block1, t_block block2)
{
	t_block next;

	next = block2->next;
	block1->size += block2->size + BLOCK_HEADER_SIZE;
	link_blocks(block1, next);
	if (!block1->next)
		update_last_block_info(region, block1);
}
