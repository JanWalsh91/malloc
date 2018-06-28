/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test12.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/23 15:15:49 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "malloc.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main()
{
	void *p;
	// p = malloc(4000);
	p = NULL;
	p = malloc(50);
	// p++;
	show_alloc_mem();
	p = realloc(p, 400);
	*((int*)p) = 40;
	show_alloc_mem();
	printf("errno: %d\n", errno);
	printf("int: %d\n", *(int*)p);
	printf("address: %p\n", p);
	free(p);
	return (0);
}