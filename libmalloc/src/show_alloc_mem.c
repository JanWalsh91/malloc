/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 10:33:46 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/09 17:02:06 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem(void)
{
	pthread_mutex_lock(&g_mutex);
	init_lists();
	show_alloc_mem_thread_unsafe();
	pthread_mutex_unlock(&g_mutex);
}

void	show_alloc_mem_thread_unsafe(void)
{
	t_region	lists[3];
	int			i;
	size_t		total_size;

	lists[0] = g_lists.tiny;
	lists[1] = g_lists.small;
	lists[2] = g_lists.large;
	total_size = 0;
	ft_putchar('\n');
	i = -1;
	while (++i < 3)
		if (lists[i])
			print_region_list(lists[i], i, &total_size);
	ft_putstr("Total : ");
	ft_putnbr(total_size);
	ft_putstr(" octets\n");
	ft_putchar('\n');
}

void	print_region_list(t_region region, int i, size_t *total_size)
{
	ft_putstr(g_lists.names[i]);
	ft_putstr(" :");
	if (!SHOW_ALLOC_MEM_SHOW_REGION_INFO)
	{
		ft_putstr(" 0x");
		putbase((size_t)(region), 16);
	}
	ft_putstr("\n");
	while (region)
	{
		print_region(region, total_size);
		region = region->next;
	}
}

void	print_region(t_region region, size_t *total_size)
{
	t_block block;

	if (SHOW_ALLOC_MEM_SHOW_REGION_INFO)
	{
		ft_putstr("region : 0x");
		putbase((size_t)region, 16);
		ft_putstr("\tsize : ");
		ft_putnbr(region->size);
		ft_putstr("\n");
	}
	block = (t_block)&region->content;
	while (block != NULL)
	{
		if (SHOW_ALLOC_MEM_SHOW_FREED_BLOCKS || !block->free)
			print_block(block, total_size);
		block = block->next;
	}
}

void	print_block(t_block block, size_t *total_size)
{
	ft_putstr("\t0x");
	putbase((size_t)&block->content, 16);
	ft_putstr(" - ");
	ft_putstr("0x");
	putbase((size_t)((char *)&block->content + block->size), 16);
	ft_putstr(" : ");
	ft_putnbr(block->size);
	ft_putstr(" octets");
	if (block->free)
		ft_putstr(" (free)");
	ft_putchar('\n');
	if (!block->free)
		*total_size += block->size;
}
