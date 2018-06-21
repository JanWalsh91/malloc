/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test10.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/21 11:39:24 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "malloc.h"

// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <stdio.h>
// #include <errno.h>

int main()
{
	void *p;

	// size_t size = 92233720368547;
	size_t size = 100000000000000;
	// size_t size = 500;
	printf("%lu\n", size );
	
	p = malloc(size);
	printf("return %p, errno: %d\n", p, errno);
	show_alloc_mem();

	p = realloc(p, size * 2);
	printf("return %p, errno: %d\n", p, errno);
	show_alloc_mem();

	printf("final\n");
	show_alloc_mem();
	return (0);
}