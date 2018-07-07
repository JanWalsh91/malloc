/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testTMP.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/07 16:19:44 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmalloc/inc/malloc.h"

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

// void					show_alloc_mem(void);

int main()
{
	// allocated TINY to have at least 3 calls to mmap
	// 1. free middle one 
	// 2. free last one
	// 3. free first one
	void *ptr;
	for (int i = 0; i < 50; i++) {
		ptr = malloc(0);
	}
	printf("ptr: %p, errno: %d\n", ptr, errno);
	show_alloc_mem();
	return (0);
}