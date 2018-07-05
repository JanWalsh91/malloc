/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region_manager2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:53:29 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/05 16:54:28 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_block		find_block_at_end_of_region(t_region region, size_t size)
{
	t_block	block;

	block = NULL;
	while (region)
	{
		if (region_has_space(region, size))
		{
			block = region->after_last_block;
			set_new_block(block, size);
			link_blocks(region->last_block, block);
			update_last_block_info(region, block);
			return (block);
		}
		region = region->next;
	}
	return (block);
}

t_block		find_block_in_freed_space(t_region region, size_t size)
{
	t_block		block;

	block = NULL;
	while (region)
	{
		block = (t_block)&region->content;
		while (block)
		{
			if (block->free && can_split_block(block, size))
			{
				block->free = 0;
				split_block(region, block, size);
				return (block);
			}
			block = block->next;
		}
		region = region->next;
	}
	return (block);
}

t_block		get_block_from_new_region(t_region region, size_t size)
{
	ft_putstr("get_block_from_new_region\n");
	t_region	new_region;

	while (region->next)
		region = region->next;
	new_region = get_new_region(size);
	if (!new_region)
		return (NULL);
	link_regions(region, new_region);
	return (find_block_at_end_of_region(region->next, size));
}

size_t		get_size_of_free_space_at_end_of_region(t_region region)
{
	char	*r_end;
	char	*b_end;

	r_end = (char *)region + region->size;
	b_end = (char *)region->after_last_block;
	return ((size_t)(r_end) - (size_t)(b_end));
}

void		update_last_block_info(t_region region, t_block block)
{
	if (block->next)
		return ;
	region->last_block = block;
	region->after_last_block = (t_block)(((char *)block) + block->size +
		BLOCK_HEADER_SIZE);
}
