/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:39 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/07 16:51:10 by jwalsh           ###   ########.fr       */
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
	// ft_putstr("free_thread_unsafe\n");
	t_region	region;
	t_block		block;

	if (!ptr)
		return ;
	// ft_putstr("A\n");
	region = get_region_containing_pointer(ptr);
	// ft_putstr("B\n");
	if (!region)
		return ;
	// ft_putstr("C\n");
	block = get_block_containing_pointer(region, ptr);
	// ft_putstr("D\n");
	if (!block)
		return ;
	// ft_putstr("E\n");
	block->free = 1;
	// ft_putstr("F\n");
	defragment(region, block);
	// ft_putstr("G\n");
	while (region->prev)
		region = region->prev;
	// ft_putstr("H\n");
	try_to_unmap_regions(region);
	// if (!try_to_unmap_regions(region))
	// 	scribble(block, 0x5);
	// ft_putstr("I\n");
	// ft_putstr("free_thread_unsafe DONE\n");
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
