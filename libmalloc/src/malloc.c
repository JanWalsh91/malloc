/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:36 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/07 16:51:27 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/types.h>

pthread_mutex_t g_mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

void		*malloc(size_t size)
{
	// ft_putstr("malloc. size: ");
	// ft_putnbr(size);
	// ft_putstr("\n");
	void	*ptr;

	ptr = NULL;
	pthread_mutex_lock(&g_mutex);
	init_lists();
	ptr = malloc_thread_unsafe(size);
	// if (ptr && (size_t)ptr % 16 != 0)
	// {
	// 	ft_putstr("not aligned\n");
	// 	putbase((size_t)ptr, 16);
	// 	ft_putchar('\n');
	// 	exit(0);
	// }
	// else
	// {
	// 	ft_putstr("address aligned: ");
	// 	putbase((size_t)ptr, 16);
	// 	ft_putchar('\n');
	// }
	// static size_t i = 0;
	// if (i > 10000)
	// 	show_alloc_mem_thread_unsafe();
	// i++;
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void		*malloc_thread_unsafe(size_t size)
{
	// ft_putstr("malloc_thread_unsafe\n");
	// show_alloc_mem_thread_unsafe();
	t_block		block;
	t_region	region;

	if (/*size <= 0 ||*/
		size >= SIZE_MAX - (BLOCK_HEADER_SIZE + REGION_HEADER_SIZE))
		return (NULL);
	block = NULL;
	region = NULL;
	size = align16(size);
	region = get_region_head(size);
	if (!region)
		return (NULL);
	block = find_block_in_freed_space(region, size);
	if (!block)
		block = find_block_at_end_of_region(region, size);
	if (!block)
		block = get_block_from_new_region(region, size);
	if (!block)
		return (NULL);
	// scribble(block, 0xA);
	// show_alloc_mem_thread_unsafe();
	// ft_putstr("malloc_thread_unsafe END\n");
	return (get_block_content(block));
}

void		init_lists(void)
{
	if (!g_lists.tiny && !g_lists.small && !g_lists.large)
	{
		g_lists.tiny = NULL;
		g_lists.small = NULL;
		g_lists.large = NULL;
		g_lists.names[0] = "TINY";
		g_lists.names[1] = "SMALL";
		g_lists.names[2] = "LARGE";
	}
}
