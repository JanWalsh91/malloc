/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:36:40 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/19 13:45:52 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	main(void)
{
	int i;
	char *addr;

	i = 0;
	// while (i < 1024)
	while (i < 2)
	{
		printf("i = %d\n", i);
		addr = (char*)malloc(10);
		show_alloc_mem();
		addr[0] = 42;
		show_alloc_mem();
		++i;
		free(addr);
		show_alloc_mem();
	}
	show_alloc_mem();
	// i = 0;
	// while (i < 10)
	// {
	// 	printf("char: %c\n", addr[0]);
	// 	++i;	
	// }
	return (0);
}