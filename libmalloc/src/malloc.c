/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:36 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/15 15:37:18 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*malloc(size_t size) {
	printf("malloc: size: %lu\n", size);

	if (size == 0) {
		return NULL;
	}
	size = align4(size);
	// get region with enough space
	t_region region = get_next_available_region(size);
	printf("\033[0;35mgot region: %p\033[0m. size: %lu, largest_free_space: %lu\n", region, region->size, region->largest_free_space);

	// get next block in that region with enough space
	t_block block = get_next_available_block_in_region(region, size);
	printf("got block: %p\n", block);
	// mark block as used
	block->free = 0;
	
	// return pointer to block content
	return (get_block_content(block));
}

