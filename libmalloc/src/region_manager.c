/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:53:29 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/15 15:41:04 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_region	*get_first_region() {
	static	t_region first_region = NULL;
	printf("get_first_region %p\n", first_region);

	return &first_region;
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
	return (region);
}

// gets next region with enough space to allocate 'size' + header
t_region	get_next_available_region(size_t size) {
	printf("get_next_available_region\n");
	t_region	*first_region = get_first_region();
	t_region 	region = NULL;
	// get a new region if none is allocated yet,
	// else get last region? or region with enough space.
	if (*first_region == NULL) {
		printf("no first region\n");
		*first_region = get_new_region(size);
		set_new_block(&((*first_region)->content), *first_region, 0);
		return(*first_region);
	}
	else {
		printf("looking for region with free space\n");
		region = *first_region;

		// get last region with enough space to allocate size + BLOCK_HEADER_SIZE
		while (region && region->largest_free_space < size + BLOCK_HEADER_SIZE) {
			region = region->next;
		}
		if (!region) {
			region = get_new_region(size);
			set_new_block(&(region->content), *first_region, 0);
		}
		return (region);
	}
}

t_block get_next_available_block_in_region(t_region region, size_t size) {
	// static int first_call = 1;
	
	printf("get_next_available_block_in_region\n");
	// no content
	// if (first_call == 1) {
	// 	first_call = 0;
	// 	printf("\tno region\n");
	// 	set_new_block(&region->content, region, size);
	// 	printf("\tnew block: %p\n", &region->content);
	// 	return (t_block)&region->content;
	// }
	t_block block = (t_block)&region->content;
	while (block->next) {
		printf("\tlooking for next available block\n");
		if (block->free && block->size >= size) {
			return block;
		}
		block = block->next;
	}
	if (!block->next) {
		return (add_new_block(block, region, size));
	}
	return NULL;
}