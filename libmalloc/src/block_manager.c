/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:59:10 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/19 14:38:03 by jwalsh           ###   ########.fr       */
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

	// printf("set_new_block. ptr: %p, next: %p, size: %lu, \n", &block, block->next, size);
}

void	*get_block_content(t_block block) {
	if (!block->free) {
		return ((void *)&block->content);	
	}
	else {
		return NULL;
	}
}

void	link_blocks(t_block prev, t_block current) {
	// printf("link blocks: prev: %p and current: %p\n", prev, current);
	if (prev)
		prev->next = current;
	current->prev = prev;
}

void	unset_block(t_region region, t_block block) {
	if (!block->prev) {
		return ;
	}

	block->prev->next = NULL;
	region->last_block = block->prev;
	region->after_last_block = block;
}