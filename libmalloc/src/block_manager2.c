/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_manager2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:59:10 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 14:16:47 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	link_blocks(t_block prev, t_block current)
{
	if (prev)
		prev->next = current;
	if (current)
		current->prev = prev;
}

int		can_split_block(t_block block, size_t size)
{
	return ((size + BLOCK_HEADER_SIZE + 4 <= block->size) ? 1 : 0);
}

void	split_block(t_region region, t_block block, size_t size)
{
	t_block	next_block;
	t_block	new_block;

	new_block = (t_block)(size_t)((char *)block + size + BLOCK_HEADER_SIZE);
	new_block->size = block->size - size - BLOCK_HEADER_SIZE;
	block->size = size;
	next_block = block->next;
	link_blocks(block, new_block);
	link_blocks(new_block, next_block);
	new_block->free = 1;
	defragment(region, new_block);
	if (!new_block->next)
		update_last_block_info(region, new_block);
}
