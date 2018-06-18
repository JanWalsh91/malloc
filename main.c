/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:18:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/18 15:05:22 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
// #include <stdio.h>
// #include <stdlib.h>

int	main(void)
{
	int *ptr = NULL;
	int *ptr2 = NULL;
	// int *ptr = NULL;
	
	printf("======= 1\n");
	ptr = (int *)malloc(sizeof(int) * 50);
	// show_alloc_mem();
	printf("======= 2\n");
	ptr2 = (int *)malloc(sizeof(int) * 50);
	// show_alloc_mem();
	// for (int i = 0; i < 5; i++) {
	// 	printf("==== %d ====\n", i);
	// 	ptr = (int *)malloc(sizeof(int) * 500);
	// 	// show_alloc_mem();
	// }

	// free(ptr2);
	// free(ptr);
	show_alloc_mem();
	ptr2 = realloc(ptr2, sizeof(int) * 100);
	show_alloc_mem();

	// printf("======= 3\n");
	// ptr = (int *)malloc(sizeof(int) * 100);
	// show_alloc_mem();
	return (0);
}