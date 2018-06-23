/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:36 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/23 13:36:00 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*malloc(size_t size) {
	printf("malloc %lu bytes\n", size);
	t_block block;
	t_region region;
	
	if (size <= 0 || size >= SIZE_MAX - (BLOCK_HEADER_SIZE + REGION_HEADER_SIZE)) {
		return (NULL);
	}
	init_lists();
	size = align4(size);
	block = NULL;
	region = NULL;
	// gets correct region head from first 
	region = get_region_head(size);
	// printf("region: %p\n", region);
	if (!region)
		return (NULL);
	block = find_block_at_end_of_region(region, size);
	// block ? printf("found block at end of region: %p\n", block) : printf("no block space at end of regions\n");
	// block ? printf("block: %p, prev: %p,  prevnext: %p\n", block, block->prev, block->prev ? block->prev->next : 0) : 0;
	if (block) return (get_block_content(block));
	block = find_block_in_freed_space(region, size);
	// block ? printf("found block in freed space: %p\n", block) : printf("no block in freed space of regions\n");
	if (block) return (get_block_content(block));
	block = get_block_from_new_region(region, size);
	if (block) {
		return (get_block_content(block));
	}
	return (NULL);
}

void	init_lists() {
	if (!g_lists.tiny && !g_lists.small && !g_lists.large) {
		// printf("\033[0;31minit_lists\033[0m\n");
		g_lists.tiny = NULL;
		g_lists.small = NULL;
		g_lists.large = NULL;
		g_lists.total_size = 0;
		g_lists.names[0] = "TINY";
		g_lists.names[1] = "SMALL";
		g_lists.names[2] = "LARGE";
	}
}
