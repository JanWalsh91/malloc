/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:39 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 11:31:56 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free(void *ptr)
{
	// ft_putstr("FREE: address: ");
	// putbase((size_t)ptr, 16);
	// ft_putchar('\n');
	pthread_mutex_lock(&mutex);
	init_lists();
	free_thread_unsafe(ptr);
	pthread_mutex_unlock(&mutex);
}

void		free_thread_unsafe(void *ptr)
{
	// ft_putstr("free_thread_unsafe START\n");
	print_thread_pid();
	// ft_putstr("free: ");
	// putbase((size_t)ptr, 16);
	// ft_putchar('\n');
	t_region	region;
	t_block		block;

	if (!ptr)
	{
		return ;
		ft_putstr("free_thread_unsafe END\n");
	}
	region = get_region_containing_pointer(ptr);
	if (!region) {
		ft_putstr("free: no region found\n");
		print_free_error(ptr);
		ft_putstr("free_thread_unsafe END\n");
		return ;
	}
	block = get_block_containing_pointer(region, ptr);
	if (!block) {
		ft_putstr("free: no block found\n");
		print_free_error(ptr);
		ft_putstr("free_thread_unsafe END\n");
		return ;
	}
	block->free = 1;
	defragment(region, block);
	while (region->prev)
		region = region->prev;
	try_to_unmap_regions(region);
	print_thread_pid();
	ft_putchar('\n');
	ft_putstr("free_thread_unsafe END\n");
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

t_block	get_block_containing_pointer(t_region region, void *ptr)
{
	t_block	block;

	block = (t_block)&region->content;
	while (block)
	{
		ft_putstr("free: check blocks:\n");
		putbase((size_t)ptr, 16);
		ft_putstr(" and ");
		putbase((size_t)get_block_content(block), 16);
		ft_putstr("\n");
		if (get_block_content(block) == ptr)
			return block;
		block = block->next;
		ft_putstr("next block: ");
		putbase((size_t)get_block_content(block), 16);
		ft_putchar('\n');
	}
	return (NULL);
}

void	defragment(t_region region, t_block block)
{
	// ft_putstr("DEFRAG around: ");
	// putbase((size_t)get_block_content(block), 16);
	// ft_putchar('\n');
	// ft_putstr("before defrag:\n");
	// show_alloc_mem_thread_unsafe();
	if (!block->free)
	{
		ft_putstr("oh no, block is not free!!\n");
		return ;
	}

	// ft_putstr("next address: ");
	// putbase((size_t)get_block_content(block->next), 16);
	// if (block->next) {
	// 	ft_putstr(", free: ");
	// 	ft_putstr(block->next->free ? "1\n" : "0\n");
	// }
	// else {
	// 	ft_putstr("\n");
	// }

	if (block->next && block->next->free)
	{
		// ft_putstr("Merge with next\n");
		merge(region, block, block->next);
	}

	// ft_putstr("prev address: ");
	// putbase((size_t)get_block_content(block->prev), 16);
	// if (block->prev) {
	// 	ft_putstr(", free: ");
	// 	ft_putstr(block->prev->free ? "1\n" : "0\n");
	// }
	// else {
	// 	ft_putstr("\n");
	// }
	
	if (block->prev && block->prev->free)
	{
		// ft_putstr("Merge with prev\n");
		merge(region, block->prev, block);

		block = block->prev;
	}
	if (!block->next)
		unset_block(region, block);
	// ft_putstr("after defrag:\n");
	// show_alloc_mem_thread_unsafe();
}

void	merge(t_region region, t_block block1, t_block block2)
{
	ft_putstr("MERGE ");
	putbase((size_t)get_block_content(block1), 16);
	ft_putstr(" and ");
	putbase((size_t)get_block_content(block2), 16);
	ft_putchar('\n');

	ft_putstr("before merge:\n");
	show_alloc_mem_thread_unsafe();
	t_block next;

	next = block2->next;
	block1->size += block2->size + BLOCK_HEADER_SIZE;
	link_blocks(block1, next);
	if (!block1->next)
		update_last_block_info(region, block1);
	ft_putstr("after merge:\n");
	show_alloc_mem_thread_unsafe();
}
