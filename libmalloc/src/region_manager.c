/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:53:29 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/18 15:22:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_region	*get_first_region(size_t size) {
	// printf("get_first_region size: %lu\n", size);
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
	region->last_block = NULL;
	region->after_last_block = (t_block)(&region->content);
	region->content = 0;
	printf("new region. size: %lu\n", region->size);
	return (region);
}

// gets next region with enough space to allocate 'size' + header
// t_region	get_next_available_region(size_t size) {
// 	printf("get_next_available_region\n");
// 	t_region	*first_region = get_first_region(size);
// 	t_region 	region = NULL;
// 	// get a new region if none is allocated yet,
// 	// else get last region? or region with enough space.
// 	if (*first_region == NULL) {
// 		printf("first region NULL\n");
// 		*first_region = get_new_region(size);
// 		return (*first_region);
// 	}
// 	else {
// 		printf("looking for region with free space\n");
// 		region = *first_region;
// 		while (region && !region_has_space(region, size)) {
// 			region = region->next;
// 		}
// 		if (!region)
// 			region = get_new_region(size);
// 		return (region);
// 	}
// }

// t_block get_next_available_block_in_region(t_region region, size_t size) {
// 	printf("get_next_available_block_in_region\n");
	
// 	t_block block = (t_block)&region->content;
// 	if (region->content == 0) {
// 		set_new_block(block, size);
// 		link_blocks(NULL, block);
// 		return block;
// 	}	
// 	while (block) {
// 		printf("next block: size: %lu, free: %d\n", block->size, block->free);
// 		if (block->free && block->size >= size) {
// 			printf("Found free block with enough space\n");
// 			set_new_block(&region->content, size);
// 			return block;
// 		}
// 		if (block->next)
// 			block = block->next;
// 		else
// 			break ;
// 	}
// 	set_new_block((t_block)((char *)block + block->size + BLOCK_HEADER_SIZE), size);
// 	link_blocks(block, (t_block)((char *)block + block->size + BLOCK_HEADER_SIZE));
// 	return block->next;
// }

int		region_has_space(t_region region, size_t size) {
	printf("region_has_space for %lu ?\n", size);
	printf("\t(char *)region + region->size - (char *)region->after_last_block >= size + BLOCK_HEADER_SIZE\n");
	printf("\t%lu + %lu - %lu >= %lu + %lu\n", (size_t)(char *)region, (size_t)(char *)region->size, (size_t)(char *)region->after_last_block, size, BLOCK_HEADER_SIZE);
	printf("\t%lu >= %lu\n", (size_t)(char *)region + (size_t)(char *)region->size - (size_t)(char *)region->after_last_block, size + BLOCK_HEADER_SIZE);
	if ((size_t)( (char *)region + region->size - (char *)region->after_last_block ) >= size + BLOCK_HEADER_SIZE) {
		printf("\t\t=> has space\n");
			return (1);
	}
	else {
		printf("\t\t=> no space\n");
			return (0);
	}
}

// new functions

// get head of correct region (tiny small large) and creates a new region if none exists
t_region	get_region_head(size_t size) {
	printf("get_region. size: %lu\n", size);
	t_region *head;
	
	head = NULL;
	head = get_first_region(size);
	// printf("head: %p\n", head);
	if (!*head) {
		*head = get_new_region(size);
	}
	return (*head);
}

t_block		find_block_at_end_of_region(t_region region, size_t size) {
	printf("find_block_at_end_of_region\n");
	t_block block;

	block = NULL;
	while (region) {
		printf("checking region %p\n", region);
		if (region_has_space(region, size)) {
			printf("region->last_block: %p\n", region->last_block);
			block = region->after_last_block;
			printf("block: %p\n", block);
			set_new_block(block, size);
			link_blocks(region->last_block, block);
			region->after_last_block = (t_block)((char *)block + size + BLOCK_HEADER_SIZE);
			region->last_block = block;
			return (block);
		}
		region = region->next;
	}
	return (block);
}

t_block		find_block_in_freed_space(t_region region, size_t size) {
	printf("find_block_in_freed_space\n");
	t_block		block;

	block = NULL;
	while (region) {
		printf("checking region %p\n", region);
		block = (t_block)&region->content;
		while (block) {
			printf("checking block: %p\n", block);
			if (block->free && block->size >= size + BLOCK_HEADER_SIZE) {
				set_new_block(block, size);
				return (block);
			}
			block = block->next;
		}		
		region = region->next;
	}
	return (block);
}

t_block		get_block_from_new_region(t_region region, size_t size) {
	printf("get_block_from_new_region\n");
	while (region->next) {
		region = region->next;
	}
	region->next = get_new_region(size);
	return (find_block_at_end_of_region(region->next, size));
}

size_t		get_size_of_free_space_at_end_of_region(t_region region) {
	char	*r_end;
	char	*b_end;

	r_end = (char *)region + region->size;
	b_end = (char *)region->after_last_block;
	return ((size_t)(r_end) - (size_t)(b_end));
}

void		update_last_block_info(t_region region, t_block block) {
	region->last_block = block;
	region->after_last_block = (t_block)((char *)block + block->size + BLOCK_HEADER_SIZE);
}
