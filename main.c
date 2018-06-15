/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:18:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/15 15:33:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
// #include <stdio.h>
// #include <stdlib.h>

int	main(int ac, char** av)
{
	(void)ac;
	(void)av;
	char *ptr = NULL;
	printf("1=======\n");
	ptr = (char *)malloc(1);
	printf("done with malloc: %p\n", ptr);
	// ptr[0] = 'A';
	// ptr[1] = 'B';
	// ptr[2] = 'C';
	// ptr[3] = 'D';
	// ptr[4] = 'E';
	// ptr[5] = 'F';
	// ptr[6] = 'G';
	// ptr[7] = '\0';
	// printf("result: %s\n", ptr);
	// printf("2=======\n");
	for (int i = 0; i < 10; i++) {
		printf("==== %d ====\n", i);
		ptr = (char *)malloc(500);
		printf("done with malloc: %p\n", ptr);
	}
	// printf("3=======\n");
	// ptr = (char *)malloc(1000);
	// printf("done with malloc: %p\n", ptr);
	// printf("4=======\n");
	// ptr = (char *)malloc(50);
	// printf("done with malloc: %p\n", ptr);
	// printf("5=======\n");
	// ptr = (char *)malloc(13505);
	// printf("done with malloc: %p\n", ptr);

	return (0);
}