/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:53:29 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 10:42:13 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** Returns the region list corresponding to allocation size request
*/

t_region	*get_first_region(size_t size) {
	// printf("get_first_region size: %lu\n", size);
	// return 0;
	if (size <= TINY_LIMIT)
		return &g_lists.tiny;
	if (size <= SMALL_LIMIT)
		return &g_lists.small;
	return &g_lists.large;
}

/*
** Returns the mininum map size depending on size to allocated
*/
size_t		get_region_min_map_size(size_t size) {
	if (size <= TINY_LIMIT) {
		return (TINY_MIN_MAP_SIZE);
	}
	else if (size <= SMALL_LIMIT) {
		return (SMALL_MIN_MAP_SIZE);
	}
	else {
		// ensure that size is a mulitple of getpagesize()
		size_t page_size = getpagesize();
		size_t page_count = (size + REGION_HEADER_SIZE) / page_size + 1;
		return (page_count * page_size);
	}
}

t_region	get_new_region(size_t size) {
	// printf("get_new_region: size: %lu\n", size);
	t_region	region;
	size_t		final_size;

	region = NULL;
	size = size + BLOCK_HEADER_SIZE;
	if (size <= BLOCK_HEADER_SIZE)
		return (NULL);

	final_size = get_region_min_map_size(size);
	// printf("final_size: %lu\n", final_size);
	region = mmap(0, final_size, PROT_READ | PROT_WRITE,
		MAP_ANON | MAP_PRIVATE, -1, 0);
	// ++mmap_calls;
	if (region == MAP_FAILED)
	{
		print_mmap_error();
		errno = ENOMEM;
		return (NULL);
	}
	region->size = final_size;
	region->next = NULL;
	region->last_block = NULL;
	region->after_last_block = (t_block)(&region->content);
	region->content = 0;
	return (region);
}

int		region_has_space(t_region region, size_t size)
{
	if (get_size_of_free_space_at_end_of_region(region) >= size + BLOCK_HEADER_SIZE)
		return (1);
	else
		return (0);
}

// get head of correct region (tiny small large) and creates a new region if none exists
t_region	get_region_head(size_t size)
{
	// printf("get_region_head. size: %lu\n", size);
	// return 0; // page reclaims: + 3
	t_region	*head;
	
	head = NULL;
	// return 0; // page reclaims: + 3
	head = get_first_region(size);
	// return 0; // page reclaims: + 5
	if (!*head)
		*head = get_new_region(size);
	return (*head);
}

t_block		find_block_at_end_of_region(t_region region, size_t size) {
	ft_putstr("find_block_at_end_of_region\n");
	t_block	block;

	block = NULL;
	while (region) {
		// printf("checking region %p\n", region);
		if (region_has_space(region, size)) {
			// !region->last_block ? 
			// printf("region->last_block: %p\n", region->last_block):
			// printf("region->last_block: %p, next: %p\n", region->last_block, region->last_block->next);
			block = region->after_last_block;
			// printf("after last block: %p\n", block);
			// Good use of set_new_block
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
	ft_putstr("find_block_in_freed_space\n");
	t_block		block;
	// t_block		next;
	// t_block		prev;

	block = NULL;
	while (region)
	{
		// printf("checking region %p\n", region);
		block = (t_block)&region->content;
		while (block)
		{
			// printf("checking block: %p, free: %s, size: %lu\n", block, block->free ? "yes" : "no", block->size);
			// if found a freed block
				// with a size that can actually fit the size of the new block, including size and header
			if (block->free && can_split_block(block, size))
			{
				block->free = 0;
				split_block(region, block, size);
				return (block);
			}
			// if (block->free && block->size >= size + BLOCK_HEADER_SIZE)
			// {
			// 	// printf("Found block\n");
			// 	prev = block->prev;
			// 	next = block->next;
			// 	block->size = size;
			// 	link_blocks(prev, block);
			// 	link_blocks(block, next);
			// 	//update end block
			// 	if (!next)
			// 		update_last_block_info(region, block);
			// 	return (block);
			// }
			block = block->next;
		}		
		region = region->next;
	}
	// printf("returning: %p\n", block);
	return (block);
}

t_block		get_block_from_new_region(t_region region, size_t size)
{
	ft_putstr("get_block_from_new_region\n");
	// printf("get_block_from_new_region\n");
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
	ft_putstr("update_last_block_info: current last: ");
	putbase((size_t)region->last_block, 16);
	ft_putstr(", new last: ");
	putbase((size_t)block, 16);
	ft_putstr("\n");
	if (block->next)
		return ;
	region->last_block = block;
	region->after_last_block = (t_block)(((char *)block) + block->size + BLOCK_HEADER_SIZE);
}

void		link_regions(t_region prev, t_region current)
{
	if (prev)
		prev->next = current;
	current->prev = prev;
}

int			region_is_free(t_region region)
{
	t_block block;

	block = (t_block)&region->content;
	while (block)
	{
		if (!block->free)
			return (0);
		block = block->next;
	}
	return (1);
}

void		try_to_unmap_regions(t_region region)
{
	int	nb_free_regions;
	int	nb_used_regions;

	nb_free_regions = 0;
	nb_used_regions = 0;
	while (region)
	{
		if (region_is_free(region))
		{
			++nb_free_regions;
			// if (nb_free_regions >= 2 && nb_used_regions > 0)
			if (nb_free_regions >= 2)
			{
				unmap_region(region);
				return ;
			}
		}
		else
			++nb_used_regions;
		if (region->next)
			region = region->next;
		else
			break ;
	}
	// if (region && nb_free_regions > 0 && nb_used_regions == 0)
	// 	unmap_all_regions(region);
}

void		unmap_all_regions(t_region region)
{
	// printf("unmap_all_regions\n");

	// printf("tiny: %p, small: %p, large: %p\n", g_lists.tiny, g_lists.small, g_lists.large);
	while (region && region->prev)
		region = region->prev;
	// printf("first region: %p\n", region);
	unmap_regions_recursively(region);
	if (region == g_lists.tiny)
		g_lists.tiny = NULL;
	else if (region == g_lists.small)
		g_lists.small = NULL;
	else if (region == g_lists.large)
		g_lists.large = NULL;
	// printf("tiny: %p, small: %p, large: %p\n", g_lists.tiny, g_lists.small, g_lists.large);
}

void		unmap_regions_recursively(t_region region)
{
	// printf("unmap_regions_recursively: %p\n", region);
	if (region && region->next)
		unmap_regions_recursively(region->next);
	unmap_region(region);
}

void		unmap_region(t_region region)
{
	// printf("unmap region %p\n", region);
	t_region	prev;
	t_region	next;

	prev = region->prev;
	// printf("check1\n");
	next = region->next;
	// printf("check2\n");
	munmap(region, region->size);
	// ++munmap_calls;
	// printf("check3\n");
	if (prev) {
		// printf("check3\n");
		prev->next = next;
	}
	// printf("end unmap region\n");
}
