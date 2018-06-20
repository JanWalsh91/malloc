/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:53:29 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/20 15:23:21 by jwalsh           ###   ########.fr       */
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
	// printf("get_new_region: size: %lu\n", size);
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
	// printf("new region. size: %lu\n", region->size);
	return (region);
}

int		region_has_space(t_region region, size_t size) {
	// printf("region_has_space for %lu ?\n", size);
	// printf("get_size_of_free_space_at_end_of_region(region) >= size + BLOCK_HEADER_SIZE\n");
	// printf("%lu >= %lu + %lu\n", get_size_of_free_space_at_end_of_region(region), size, BLOCK_HEADER_SIZE);
	if (get_size_of_free_space_at_end_of_region(region) >= size + BLOCK_HEADER_SIZE) {
		// printf("\t\t=> has space\n");
			return (1);
	}
	else {
		// printf("\t\t=> no space\n");
			return (0);
	}
}

// new functions

// get head of correct region (tiny small large) and creates a new region if none exists
t_region	get_region_head(size_t size) {
	// printf("get_region. size: %lu\n", size);
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
	// printf("find_block_at_end_of_region\n");
	t_block block;

	block = NULL;
	while (region) {
		// printf("checking region %p\n", region);
		if (region_has_space(region, size)) {
			// !region->last_block ? 
			// printf("region->last_block: %p\n", region->last_block):
			// printf("region->last_block: %p, next: %p\n", region->last_block, region->last_block->next);
			block = region->after_last_block;
			// printf("after last block: %p\n", block);
			set_new_block(block, size);
			link_blocks(region->last_block, block);
			update_last_block_info(region, block);
			// if (block && block->prev)
			// 	printf("freed block: %p linked with next %p current block: %p\n", block->prev, block->prev->next, block);
			return (block);
		}
		region = region->next;
	}
	return (block);
}

t_block		find_block_in_freed_space(t_region region, size_t size) {
	// printf("find_block_in_freed_space for size %lu\n", size);
	t_block		block;

	block = NULL;
	while (region) {
		// printf("checking region %p\n", region);
		block = (t_block)&region->content;
		while (block) {
			// printf("checking block: %p, free: %s, size: %lu\n", block, block->free ? "yes" : "no", block->size);
			if (block->free && block->size >= size + BLOCK_HEADER_SIZE) {
				set_new_block(block, size);
				//update end block
				update_last_block_info(region, block);
				return (block);
			}
			block = block->next;
		}		
		region = region->next;
	}
	return (block);
}

t_block		get_block_from_new_region(t_region region, size_t size) {
	// printf("get_block_from_new_region\n");
	t_region	new_region;

	while (region->next) {
		region = region->next;
	}
	new_region = get_new_region(size);
	link_regions(region, new_region);
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

void		link_regions(t_region prev, t_region current) {
	if (prev)
		prev->next = current;
	current->prev = prev;
}

int			region_is_free(t_region region) {
	t_block block;

	block = (t_block)&region->content;
	while (block) {
		if (!block->free) {
			return (0);
		}
		block = block->next;
	}
	return (1);
}

void		try_to_unmap_regions(t_region region) {
	int	nb_free_regions;

	nb_free_regions = 0;
	while (region) {
		if (region_is_free(region)) {
			++nb_free_regions;
			if (nb_free_regions >= 2) {
				unmap_region(region);
				return ;
			}
		}
		region = region->next;
	}
}

// can never be called on first region
void		unmap_region(t_region region) {
	printf("unmap region\n");
	t_region prev;
	t_region next;

	if (!region->prev)
		return ;
	prev = region->prev;
	next = region->next;
	munmap(region, region->size);
	prev->next = next;
}