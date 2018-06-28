/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test11.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/23 14:23:50 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "malloc.h"

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
	p++;
	free(p);

	// show_alloc_mem();
	printf("errno: %d\n", errno);
	return (0);
}