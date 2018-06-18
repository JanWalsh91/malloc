/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:33 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/18 15:18:20 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc(void *ptr, size_t size) {	
	printf("realloc size: %lu\n", size);
	t_region	region;
	t_block		block;
	
	if (size == 0) {
		return (NULL);
	}
	init_lists();
	size = align4(size);
	
	region = get_region_containing_pointer(ptr);
	printf("region with pointer: %p\n", region);
	if (!region)
		return (ptr);
	block = get_block_containing_pointer(region, ptr);
	printf("block with pointer: %p\n", block);
	if (!block)
		return (ptr);

	printf("size <= block->size\n");
	printf("%lu <= %lu\n", size, block->size);
	if (size <= block->size) {
		printf("size + BLOCK_HEADER_SIZE + 4 <= block->size\n");
		printf("%lu + %lu + 4 <= %lu\n", size, BLOCK_HEADER_SIZE, block->size);
		if (size + BLOCK_HEADER_SIZE + 4 <= block->size) {
			split_block(block, size);
			return (ptr);
		}
		else {
			return (ptr);
		}
	}
	else {
		if (!block->next) {
			if (get_size_of_free_space_at_end_of_region(region) + block->size >= size) {
				block->size = size;
			}
		}
		free(ptr);
		void *new_ptr = malloc(size);
		memcpy(new_ptr, ptr, block->size);
		return (new_ptr);
	}
	return (ptr);
}

void	split_block(t_block block, size_t size) {
	printf("split_block\n");
	t_block tmp;
	t_block new_block;
	
	new_block = (t_block)(size_t)((char *)block + block->size + BLOCK_HEADER_SIZE); 
	set_new_block(new_block, block->size - size - BLOCK_HEADER_SIZE);
	block->size = size;
	tmp = block->next;
	link_blocks(block, new_block);
	new_block->next = tmp;
	new_block->free = 1;
}