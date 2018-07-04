/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 14:00:36 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 10:14:32 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <sys/types.h>

pthread_mutex_t mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

void		*malloc(size_t size)
{
	ft_putstr("MALLOC: size: ");
	ft_putnbr(size);
	ft_putchar('\n');
	void	*ptr;

	ptr = NULL;
	pthread_mutex_lock(&mutex);
	ft_putstr("malloc: lock mutex\n");
	print_thread_pid();
	init_lists();
	ptr = malloc_thread_unsafe(size);
	ft_putstr("malloc: unlock mutex\n");
	print_thread_pid();
	pthread_mutex_unlock(&mutex);
	return (ptr);
}

void		*malloc_thread_unsafe(size_t size)
{
	ft_putstr("malloc_thread_unsafe START\n");
	print_thread_pid();
	// printf("malloc %lu bytes\n", size);
	// ft_putstr("malloc: size: ");
	// ft_putnbr(size);
	// ft_putstr("\n");
	t_block		block;
	t_region	region;

	if (size <= 0 ||
		size >= SIZE_MAX - (BLOCK_HEADER_SIZE + REGION_HEADER_SIZE))
		return (NULL);
	block = NULL;
	region = NULL;
	size = align4(size);
	region = get_region_head(size);
	if (!region)
	{
		return (NULL);
	}
	// ft_putstr("check1\n");
	block = find_block_in_freed_space(region, size);
	// ft_putstr("check2\n");
	if (!block)
		block = find_block_at_end_of_region(region, size);
	// ft_putstr("check3\n");
	if (!block)
		block = get_block_from_new_region(region, size);
	// ft_putstr("check4\n");
	if (!block)
	{
		// ft_putstr("check5\n");
		return (NULL);
	}
	ft_putstr("malloc_thread_unsafe END\n");
	print_thread_pid();
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
		// mmap_calls = 0;
		// munmap_calls = 0;
	}
}
