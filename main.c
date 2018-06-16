/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:18:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/16 11:47:35 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
// #include <stdio.h>
// #include <stdlib.h>

int	main(void)
{
	char *ptr = NULL;
	
	printf("======= 1\n");
	ptr = (char *)malloc(10);
	printf("======= 2\n");
	ptr = (char *)malloc(20);
	printf("======= 3\n");
	ptr = (char *)malloc(30000);
	// printf("======= 1\n");
	// ptr = (char *)malloc(1);
	// printf("======= 1\n");
	// ptr = (char *)malloc(1);
	// printf("done with malloc: %p\n", ptr);

	// printf("======= 2\n");
	// ptr = (char *)malloc(1000);
	// printf("done with malloc: %p\n", ptr);
	
	// printf("======= 3\n");
	// ptr = (char *)malloc(10000);
	// printf("done with malloc: %p\n", ptr);

	show_alloc_mem();

	// printf("2=======\n");
	// for (int i = 0; i < 10; i++) {
	// 	printf("==== %d ====\n", i);
	// 	ptr = (char *)malloc(500);
	// 	printf("done with malloc: %p\n", ptr);
	// }

	return (0);
}