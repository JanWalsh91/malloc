/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:59:10 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/15 15:13:16 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	 set_new_block(void* ptr, t_region region, size_t size) {
	printf("set_new_block\n");
	t_block block = (t_block)ptr;

	printf("A\n");
	block->size = size;
	printf("B\n");
	block->prev = NULL;
	block->next = NULL;
	block->content = 0;

	printf("set_new_block. ptr: %p, next: %p, size: %lu, \n", ptr, block->next, size);
	//update largest available space
	(void)region;
}

t_block		add_new_block(t_block block, t_region region, size_t size) {
	printf("add_new_block\n");
	block->next = (t_block)((char *)(&block->content) + block->size - 4);
	printf("A\n");
	set_new_block(block->next, region, size);
	printf("B\n");
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