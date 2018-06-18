/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:18:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/18 13:14:44 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
// #include <stdio.h>
// #include <stdlib.h>

int	main(void)
{
	int *ptr = NULL;
	
	// printf("======= 1\n");
	// ptr = (int *)malloc(sizeof(int));
	// show_alloc_mem();
	// printf("======= 2\n");
	// ptr = (int *)malloc(sizeof(int) * 2);
	// show_alloc_mem();
	for (int i = 0; i < 3; i++) {
		printf("==== %d ====\n", i);
		ptr = (int *)malloc(sizeof(int) * 500);
		show_alloc_mem();
	}

	return (0);
}