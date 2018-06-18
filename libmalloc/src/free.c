/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:39 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/18 14:28:43 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free(void *ptr) {
	printf("free: %p\n", ptr);

	t_region	region;
	t_block		block;

	region = get_region_containing_pointer(ptr);
	printf("region with pointer: %p\n", region);
	if (!region)
		return ; 
	block = get_block_containing_pointer(region, ptr);
	printf("block with pointer: %p\n", block);
	block->free = 1;
	if (!block)
		return ;
	defragment(region, block);
}

t_region	get_region_containing_pointer(void *ptr) {
	t_region	lists[3];
	t_region	region;
	int i;

	lists[0] = g_lists.tiny;
	lists[1] = g_lists.small;
	lists[2] = g_lists.large;
	i = -1;
	while (++i < 3)
	{
		if (lists[i]) {
			region = lists[i];
			while (region) {
				if ((size_t)region < (size_t)ptr && (size_t)ptr < (size_t)((char *)region + region->size))
					return (region);
				region = region->next;
			}
		}
	}
	return (NULL);
}

t_block	get_block_containing_pointer(t_region region, void *ptr) {
	t_block	block;

	block = (t_block)&region->content;
	while (block) {
		if (get_block_content(block) == ptr) {
			return block;
		}
		block = block->next;
	}
	return (NULL);
}

void	defragment(t_region region, t_block block) {
	printf("defrag\n");
	if (!block->free) {
		return ;
	}
	if (block->next && block->next->free) {
		merge(block, block->next);
	}
	if (block->prev && block->prev->free) {
		merge(block->prev, block);
		block = block->prev;
	}
	if (!block->next) {
		unset_block(region, block);
	}
}

void	merge(t_block block1, t_block block2) {
	block1->next = block2->next;
	block1->size += block2->size + BLOCK_HEADER_SIZE;
}