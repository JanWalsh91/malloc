/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 10:33:46 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 13:49:04 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem()
{
	pthread_mutex_lock(&mutex);
	init_lists();
	show_alloc_mem_thread_unsafe();
	pthread_mutex_unlock(&mutex);
}

void	show_alloc_mem_thread_unsafe()
{
	// printf("show_alloc_mem\n");
	t_region	lists[3];
	int			i;
	size_t		total_size;

	lists[0] = g_lists.tiny;
	lists[1] = g_lists.small;
	lists[2] = g_lists.large;
	total_size = 0;
	ft_putchar_fd('\n', g_fd);
	if (g_fd != 1)
		print_timestamp();
	i = -1;
	while (++i < 3)
		if (lists[i])
			print_region_list(lists[i], i, &total_size);
	ft_putstr_fd("Total : ", g_fd);
	ft_putnbr_fd(total_size, g_fd);
	ft_putstr_fd(" octets\n", g_fd);
	ft_putchar_fd('\n', g_fd);
	// printf("mmap calls: %d\n", mmap_calls);
	// printf("munmap calls: %d\n", munmap_calls);
}


void	print_region_list(t_region region, int i, size_t *total_size)
{
	t_block block;
	
	ft_putstr_fd(g_lists.names[i], g_fd);
	// ft_putstr_fd(" : 0x", g_fd);
	// putbase_fd((size_t)&region->content, 16, g_fd);
	// putbase_fd((size_t)(region), 16, g_fd);
	ft_putchar_fd('\n', g_fd);
	while (region)
	{
		// printf("Mapping: %p : size %lu\n", region, region->size);
		block = (t_block)&region->content;
		while (block != NULL)
		{
			print_block(block, total_size);
			block = block->next;
		}
		region = region->next;
	}
}

void	print_block(t_block block, size_t *total_size)
{
	ft_putstr_fd("0x", g_fd);
	putbase_fd((size_t)&block->content, 16, g_fd);
	ft_putstr_fd(" - ", g_fd);
	ft_putstr_fd("0x", g_fd);
	putbase_fd((size_t)((char *)&block->content + block->size), 16, g_fd);
	ft_putstr_fd(" : ", g_fd);
	ft_putnbr_fd(block->size, g_fd);
	ft_putstr_fd(" octets", g_fd);
	if (block->free)
		ft_putstr_fd(" (free)", g_fd);
	ft_putchar_fd('\n', g_fd);

	// ft_putstr_fd("\tprev: ", g_fd);
	// putbase_fd((size_t)get_block_content(block->prev), 16, g_fd);
	// ft_putstr_fd("\tnext: ", g_fd);
	// putbase_fd((size_t)get_block_content(block->next), 16, g_fd);
	// ft_putstr_fd("\n", g_fd);
	
	if (!block->free)
		*total_size += block->size;
}

void	print_timestamp()
{
	time_t	ltime;
	struct	timeval	t;

	
    ltime = time(NULL);
    ft_putstr_fd(asctime(localtime(&ltime)), g_fd);

	gettimeofday(&t, NULL);
	ft_putstr_fd("milliseconds: ", g_fd);
	ft_putnbr_fd(t.tv_usec, g_fd);
	ft_putstr_fd("\n", g_fd);
}
