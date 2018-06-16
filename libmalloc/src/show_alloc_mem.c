/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 10:33:46 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/16 14:21:04 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_alloc_mem() {
	t_region lists[3];
	int i;

	lists[0] = g_lists.tiny;
	lists[1] = g_lists.small;
	lists[2] = g_lists.large;
	ft_putchar('\n');
	i = -1;
	while (++i < 3)
	{
		if (lists[i])
			print_region(lists[i], i);
	}
	ft_putstr("Total : ");
	ft_putnbr(g_lists.total_size);
	ft_putstr(" octets\n");
}


void	print_region(t_region region, int i) {
	t_block block;
	
	ft_putstr(g_lists.names[i]);
	ft_putstr(" : 0x");
	// putbase((size_t)&region->content, 16);
	putbase((size_t)(region), 16);
	ft_putchar('\n');
	block = (t_block)&region->content;
	while (block != NULL)
	{
		print_block(block);
		block = block->next;
	}
}

void	print_block(t_block block) {
	ft_putstr("0x");
	putbase((size_t)&block->content, 16);
	ft_putstr(" - ");
	ft_putstr("0x");
	putbase((size_t)((char *)&block->content + block->size), 16);
	ft_putstr(" : ");
	ft_putnbr(block->size);
	ft_putstr(" octets\n");
}
