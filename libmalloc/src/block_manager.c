/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:59:10 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/15 12:34:44 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	 set_new_block(void* ptr, size_t size) {
	printf("set_new_block. ptr: %p, size: %lu\n", ptr, size);
	t_block block = (t_block)ptr;

	block->size = size;
	block->next = NULL;
	block->used = 1;
}

t_block get_next_available_block_in_region(t_region region, size_t size) {
	printf("get_next_available_block_in_region\n");
	// no content
	if (region->content[0] == 0) {
		printf("empty region\n");
		set_new_block(&region->content[1], size);
		printf("new block: %p\n", &region->content[1]);
		region->content[0] = 1;
		return (t_block)&region->content[1];
	}
	t_block block = (t_block)&region->content[1];
	while (block->next) {
		printf("looking for next available block\n");
		if (!block->used && block->size >= size) {
			return block;
		}
		block = block->next;
	}
	if (!block->next) {
		set_new_block(block->next, size);
	}
	(void)size;
	(void)region;
	return NULL;
}