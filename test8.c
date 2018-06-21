/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/21 11:27:26 by jwalsh           ###   ########.fr       */
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
	size_t size = 900000000000000;
	printf("%lu\n", size );
	p = malloc(size);
	printf("return %p, errno: %d\n", p, errno);
	// p = malloc(size);
	// printf("return %p, errno: %d\n", p, errno);
	// show_alloc_mem();
	return (0);
}