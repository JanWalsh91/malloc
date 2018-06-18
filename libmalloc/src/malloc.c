/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:36 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/18 13:42:41 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

// void		*malloc(size_t size) {
// 	printf("malloc: size: %lu\n", size);

// 	if (size == 0) {
// 		return NULL;
// 	}
// 	init_lists();
// 	size = align4(size);
// 	// get region with enough space
// 	t_region region = get_next_available_region(size);
// 	printf("\033[0;35mgot region: %p\033[0m. size: %lu\n", region, region->size);

// 	// get next block in that region with enough space
// 	t_block block = get_next_available_block_in_region(region, size);
// 	printf("got block: %p\n", block);
// 	// mark block as used
// 	block->free = 0;
	
// 	// return pointer to block content
// 	return (get_block_content(block));
// }

void	init_lists() {
	if (!g_lists.tiny && !g_lists.small && !g_lists.large) {
		printf("\033[0;31minit_lists\033[0m\n");
		g_lists.tiny = NULL;
		g_lists.small = NULL;
		g_lists.large = NULL;
		g_lists.total_size = 0;
		g_lists.names[0] = "TINY";
		g_lists.names[1] = "SMALL";
		g_lists.names[2] = "LARGE";
	}
}


void		*malloc(size_t size) {
	t_block block;
	t_region region;
	
	if (size == 0) {
		return NULL;
	}
	init_lists();
	size = align4(size);
	block = NULL;
	region = NULL;
	// gets correct region head from first 
	region = get_region_head(size);
	printf("region: %p\n", region);
	block = find_block_at_end_of_region(region, size);
	block ? printf("found block: %p\n", block) : printf("no block space at end of regions\n");
	if (block) return (get_block_content(block));
	block = find_block_in_freed_space(region, size);
	block ? printf("found block: %p\n", block) : printf("no block in freed space of regions\n");
	if (block) return (get_block_content(block));
	block = get_block_from_new_region(region, size);
	if (block) {
		return (get_block_content(block));
	}
	return NULL;
}