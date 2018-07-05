/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 10:33:46 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/05 16:58:44 by jwalsh           ###   ########.fr       */
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
	t_block block;

	ft_putstr(g_lists.names[i]);
	ft_putstr(" : 0x");
	putbase((size_t)(region), 16);
	
	ft_putstr("\tSize: ");
	ft_putnbr(region->size);
	
	ft_putstr("\n");
	while (region)
	{
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
	ft_putstr("0x");
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
