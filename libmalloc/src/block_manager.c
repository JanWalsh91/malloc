/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:59:10 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/18 14:32:59 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	 set_new_block(void *ptr, size_t size) {
	t_block	block;

	block = (t_block)ptr;
	// size of allocation
	block->size = size;
	block->prev = NULL;
	block->next = NULL;
	block->content = 0;
	block->free = 0;

	printf("set_new_block. ptr: %p, next: %p, size: %lu, \n", &block, block->next, size);
	//update largest available space
	// printf("space at end: %lu\n", region->space_at_end);
	// region->space_at_end -= (size + BLOCK_HEADER_SIZE);
	// printf("space at endL %lu\n", region->space_at_end);
	// region->largest_free_space = region->space_at_end;
	// printf("largest_free_space: %lu\n", region->largest_free_space);
}

// t_block		add_new_block(t_block block, t_region region, size_t size) {
// 	printf("add_new_block\n");
// 	block->next = (t_block)((char *)(&block->content) + block->size - 4);
// 	set_new_block(block->next, region, size);
// 	return block->next;
// }


void	*get_block_content(t_block block) {
	if (!block->free) {
		return ((void *)&block->content);	
	}
	else {
		return NULL;
	}
}

void	link_blocks(t_block prev, t_block current) {
	if (prev)
		prev->next = current;
	current->prev = prev;
	current->next = NULL;
}

void	unset_block(t_region region, t_block block) {
	// dont unset it if its the first
	if (!block->prev) {
		return ;
	}

	block->prev->next = NULL;
	region->last_block = block->prev;
	region->after_last_block = block;
}