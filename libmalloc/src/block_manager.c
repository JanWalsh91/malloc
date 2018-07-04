/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:59:10 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 17:36:08 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		set_new_block(void *ptr, size_t size)
{
	t_block	block;

	block = (t_block)ptr;
	block->size = size;
	block->prev = NULL;
	block->next = NULL;
	block->content = 0;
	block->free = 0;
}

void		*get_block_content(t_block block)
{
	if (block)
		return ((void *)&block->content);
	else
		return (NULL);
}

void		unset_block(t_region region, t_block block)
{
	if (!block->prev)
		return ;
	block->prev->next = NULL;
	update_last_block_info(region, block->prev);
}

t_block		get_block_containing_pointer(t_region region, void *ptr)
{
	t_block	block;

	block = (t_block)&region->content;
	while (block)
	{
		if (get_block_content(block) == ptr)
			return (block);
		block = block->next;
	}
	return (NULL);
}
