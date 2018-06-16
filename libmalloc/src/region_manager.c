/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:53:29 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/16 14:27:57 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_region	*get_first_region(size_t size) {
	printf("get_first_region size: %lu\n", size);
	if (size <= TINY_LIMIT)
		return &g_lists.tiny;
	if (size <= SMALL_LIMIT)
		return &g_lists.small;
	return &g_lists.large;
}

t_region	get_new_region(size_t size) {
	printf("get_new_region: size: %lu\n", size);
	// use mmap to allocate region
	t_region region;

	region = NULL;
	size = size + BLOCK_HEADER_SIZE;
	// size + s_regionize must be a multiple of page size
	// TODO: adjust according to TINY SMALL and LARGE allocations
	size_t page_size = getpagesize();
	// printf("page size: %lu\n", page_size);
	size_t page_count = (size + REGION_HEADER_SIZE) / page_size + 1;
	// printf("page_count: %lu\n", page_count);
	size_t final_size = page_count * page_size;
	// printf("final_size: %lu\n", final_size);
	
	region = mmap(0, final_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	region->nb_pages = page_count;
	region->size = final_size;
	region->next = NULL;
	region->content = 0;
	region->largest_free_space = final_size - REGION_HEADER_SIZE;
	region->space_at_end = region->largest_free_space;
	printf("new region. size: %lu, free_space: %lu\n", region->size, region->largest_free_space);
	return (region);
}

// gets next region with enough space to allocate 'size' + header
t_region	get_next_available_region(size_t size) {
	printf("get_next_available_region\n");
	t_region	*first_region = get_first_region(size);
	t_region 	region = NULL;
	// get a new region if none is allocated yet,
	// else get last region? or region with enough space.
	if (*first_region == NULL) {
		printf("first region NULL\n");
		*first_region = get_new_region(size);
		return (*first_region);
	}
	else {
		printf("looking for region with free space\n");
		region = *first_region;
		while (region && region->largest_free_space < size + BLOCK_HEADER_SIZE) {
			region = region->next;
		}
		if (!region)
			region = get_new_region(size);
		return (region);
	}
}

t_block get_next_available_block_in_region(t_region region, size_t size) {
	printf("get_next_available_block_in_region\n");
	
	t_block block = (t_block)&region->content;
	if (region->content == 0) {
		set_new_block(block, size);
		link_blocks(NULL, block);
		update_region_header(region, size);
		return block;
	}	
	while (block) {
		printf("next block: size: %lu, free: %d\n", block->size, block->free);
		if (block->free && block->size >= size) {
			printf("Found free block with enough space\n");
			set_new_block(&region->content, size);
			return block;
		}
		if (block->next)
			block = block->next;
		else
			break ;
	}
	set_new_block((t_block)((char *)block + block->size + BLOCK_HEADER_SIZE), size);
	link_blocks(block, (t_block)((char *)block + block->size + BLOCK_HEADER_SIZE));
	return block->next;
}

void	update_region_header(t_region region, size_t size) {
	
}