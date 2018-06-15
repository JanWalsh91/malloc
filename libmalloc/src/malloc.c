/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:36 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/15 12:35:15 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*malloc(size_t size) {
	printf("size: %lu\n", size);
	(void)size;

	// get region with enough available space
	// size must be adjusted to contain block
	size = size + BLOCK_SIZE;
	t_region region = get_next_available_region(size);
	t_block block = get_next_available_block_in_region(region, size);
	// get next available block in that region
	(void)region;
	return (block);
}

