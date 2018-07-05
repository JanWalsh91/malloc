/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test14.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/05 16:57:25 by jwalsh           ###   ########.fr       */
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
	int i = 0;
	void *ptr;

	while (i < 10)
	{
		ptr = malloc(1020);
		++i;
	}
	show_alloc_mem();
	return (0);
}