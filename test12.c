/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test12.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 12:48:37 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "malloc.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

// scribble test

int main()
{
	char *ptr;
	char *ptr2;

	// setenv("MALLOC_SCRIBBLE", "1", 1);
	ptr = (char *)malloc(100);

	printf("address: %p\n", ptr);
	printf("value: %d\n", (int)ptr[0]);

	free(ptr);

	printf("address: %p\n", ptr);
	printf("value: %d\n", (int)ptr[0]);

	ptr[0] = 42;

	malloc(500);
	malloc(500);
	ptr = realloc(ptr, 200);

	printf("address: %p\n", ptr);
	printf("value: %d\n", (int)ptr[0]);

	// unsetenv("MALLOC_SCRIBBLE");
	return (0);
}
