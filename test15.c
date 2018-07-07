/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test15.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/07 10:42:52 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmalloc/inc/malloc.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int main()
{
	// allocated TINY to have at least 3 calls to mmap
	// 1. free middle one 
	// 2. free last one
	// 3. free first one
	int i = 0;
	void *ptr[50];

	while (i < 20)
	{
		ptr[i] = malloc(900);
		++i;
	}
	show_alloc_mem();
	free(ptr[1]);
	free(ptr[2]);
	free(ptr[3]);
	free(ptr[4]);
	show_alloc_mem();
	return (0);
}