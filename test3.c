/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:36:40 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/19 15:00:27 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	main(void)
{
	int i;
	char *addr;

	i = 0;
	while (i < 100)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		show_alloc_mem();
		free(addr);
		show_alloc_mem();
		i++;
	}
	show_alloc_mem();	
	return (0);
}