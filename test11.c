/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test11.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/23 13:35:52 by jwalsh           ###   ########.fr       */
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
	p = malloc(4000);
	p = malloc(4096 * 4096);
	p = malloc(4096 * 4096 * 32);
	show_alloc_mem();
	return (0);
}