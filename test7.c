/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 12:24:31 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "malloc.h"

void print_mem_color()
{
	write(1, "\x1b[31m", 5);
	show_alloc_mem();
	write(1, "\x1b[0m", 4);
}

int main()
{
	void*	ptr = NULL;
	void*	ptr2 = NULL;
	void*	ptr3 = NULL;
	
	ptr = malloc(200);
	print_mem_color();

	free(ptr);
	print_mem_color();

	ptr2 = malloc(400);
	print_mem_color();

	ptr2 = realloc(ptr2, 500); 
	print_mem_color();

	return (0);
}