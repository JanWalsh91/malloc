/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:59:10 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 11:01:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	 set_new_block(void *ptr, size_t size)
{
	t_block	block;

	block = (t_block)ptr;
	block->size = size;
	block->prev = NULL;
	block->next = NULL;
	block->content = 0;
	block->free = 0;
}

void	*get_block_content(t_block block)
{
	if (block/* && !block->free */)
		return ((void *)&block->content);
	else
		return (NULL);
}

void	link_blocks(t_block prev, t_block current)
{
	ft_putstr("link blocks ");
	putbase((size_t)get_block_content(prev), 16);
	ft_putstr(" and ");
	putbase((size_t)get_block_content(current), 16);
	ft_putchar('\n');
	if (prev)
		prev->next = current;
	if (current)
		current->prev = prev;
}

void	unset_block(t_region region, t_block block)
{
	ft_putstr("unset block\n");
	putbase((size_t)get_block_content(block), 16);
	ft_putstr("\n");
	if (!block->prev)
		return ;

	block->prev->next = NULL;
	update_last_block_info(region, block->prev);
	// region->last_block = block->prev;
	// region->after_last_block = block;
}

// block to try to split
// size of other block (excluding header)
int		can_split_block(t_block block, size_t size)
{
	return ((size + BLOCK_HEADER_SIZE + 4 <= block->size) ? 1 : 0);
}

void	split_block(t_region region, t_block block, size_t size)
{
	ft_putstr("split_block\n");
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
