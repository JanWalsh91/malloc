/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:53:29 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/11 16:01:27 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

region_t	*get_first_region() {
	static	region_t first_region = NULL;

	return &first_region;
}

region_t	get_new_region(size_t size) {
	// use mmap to allocate region
	region_t region;

	region = NULL;
	// size + region_size must be a multiple of page size
	// TODO: adjust according to TINY SMALL and LARGE allocations
	size_t page_size = getpagesize();
	printf("page size: %lu\n", page_size);
	size_t page_count = (size + REGION_SIZE) / page_size + 1;
	printf("page_count: %lu\n", page_count);
	size_t final_size = page_count * page_size;
	printf("final_size: %lu\n", final_size);
	
	region = mmap(0, final_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	region->nb_pages = page_count;
	region->blocks = NULL;
	region->total_size = final_size;
	region->next = NULL;
	return (region);
}

// 
region_t	get_next_available_region(size_t size) {
	region_t	region = *get_first_region();
	
	// get a new region if none is allocated yet,
	// else get last region? or region with enough space.
	if (region == NULL) {
		region = get_new_region(size);
	}
	else {
		// get last region
		while (region) {
			region = region->next;
		}
		// while (region && !region_has_space(region)) {
		// 	region = region->next;
		// }
		if (!region) {
			region = get_new_region(size);
		}
	}
	return (region);
}