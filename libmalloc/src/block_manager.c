/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:59:10 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/15 15:30:16 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	 set_new_block(void* ptr, t_region region, size_t size) {
	printf("set_new_block\n");
	t_block block = (t_block)ptr;

	block->size = size;
	block->prev = NULL;
	block->next = NULL;
	block->content = 0;

	printf("set_new_block. ptr: %p, next: %p, size: %lu, \n", ptr, block->next, size);
	//update largest available space
	region->space_at_end -= (size + BLOCK_HEADER_SIZE);
	region->largest_free_space = region->space_at_end;
	printf("largest_free_space: %lu\n", region->largest_free_space);
	(void)region;
}

t_block		add_new_block(t_block block, t_region region, size_t size) {
	printf("add_new_block\n");
	block->next = (t_block)((char *)(&block->content) + block->size - 4);
	set_new_block(block->next, region, size);
	return block->next;
}

void	*get_block_content(t_block block) {
	if (!block->free) {
		return ((void *)&block->content);	
	}
	else {
		return NULL;
	}
}