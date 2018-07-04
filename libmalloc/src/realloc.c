/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:33 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 16:52:56 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
	ft_putstr("REALLOC: address: ");
	putbase((size_t)ptr, 16);
	ft_putstr(", size: ");
	ft_putnbr(size);
	ft_putchar('\n');
	void	*ret;

	ret = NULL;
	pthread_mutex_lock(&mutex);
	ft_putstr("realloc: lock mutex\n");
	init_lists();
	ret = realloc_thread_unsafe(ptr, size);
	ft_putstr("realloc: unlock mutex\n");
	pthread_mutex_unlock(&mutex);
	return (ret);
}

void		*realloc_thread_unsafe(void *ptr, size_t size) {
	ft_putstr("realloc_thread_unsafe START\n");
	ft_putstr("realloc: address: ");
	putbase((size_t)ptr, 16);
	ft_putstr(", size: ");
	ft_putnbr(size);
	ft_putchar('\n');
	t_region	region;
	t_block		block;
	
	
	// ft_putstr("check1\n");
	if (!ptr)
		return (malloc_thread_unsafe(size));
	if (size <= 0)
		return (NULL);
	
	size = align4(size);
	// ft_putstr("check2\n");
	
	region = get_region_containing_pointer(ptr);
	// printf("region with pointer: %p\n", region);
	// ft_putstr("check3\n");
	if (!region) {
		ft_putstr("realloc: did not find region with pointer: \n");
		putbase((size_t)ptr, 16);
		ft_putchar('\n');
		ft_putstr("realloc_thread_unsafe END\n");
		return (NULL);
	}
	// ft_putstr("check4\n");
	block = get_block_containing_pointer(region, ptr);
	// printf("block with pointer: %p\n", block);
	// ft_putstr("check5\n");
	if (!block)
	{
		ft_putstr("realloc: did not find block with pointer\n");
		ft_putstr("realloc_thread_unsafe END\n");
		return (NULL);
	}
	// ft_putstr("check6\n");
	// printf("size <= block->size\n");
	// printf("%lu <= %lu\n", size, block->size);
	if (size <= block->size) {
		ft_putstr("realloc: update header size cos new size is smaller\n");
		// printf("size + BLOCK_HEADER_SIZE + 4 <= block->size\n");
		// printf("%lu + %lu + 4 <= %lu\n", size, BLOCK_HEADER_SIZE, block->size);
		if (can_split_block(block, size))
		{
			ft_putstr("realloc: split block\n");
			block->free = 0;
			split_block(region, block, size);
		}

		ft_putstr("realloc_thread_unsafe END\n");

		return (ptr);
	}
	// ft_putstr("check7\n");
	// return ptr; ////////
	// if (1)
	// 	return ptr;
	if (!block->next && get_size_of_free_space_at_end_of_region(region) +
		block->size >= size)
	{
		ft_putstr("realloc: update size cos space at end of region\n");
		block->size = size;
		update_last_block_info(region, block);

		ft_putstr("realloc_thread_unsafe END\n");

		return (get_block_content(block));
	}
	
	// return ptr; /////////

	ft_putstr("realloc: free and malloc\n");

	show_alloc_mem_thread_unsafe();

	// if MALLOC_SCRIBBLE is set, unset it during malloc_thread_unsafe and free_thread_unsafe
	// const	char *scribble = getenv("MALLOC_SCRIBBLE");
	// const char	*scribble;
	void		*new_ptr;
	
	new_ptr = malloc_thread_unsafe(size);
	// scribble = getenv("MALLOC_SCRIBBLE");
	// if (scribble)
	// 	unsetenv("MALLOC_SCRIBBLE");
	if (new_ptr)
		memcpy(new_ptr, ptr, block->size);
	free_thread_unsafe(ptr);
	// if (scribble)
	// 	setenv("MALLOC_SCRIBBLE", scribble, 1);

	ft_putstr("realloc: AFTER free and malloc\n");
	show_alloc_mem_thread_unsafe();

	ft_putstr("realloc_thread_unsafe END\n");

	return (new_ptr);
}
