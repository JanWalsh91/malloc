/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/19 15:08:29 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main()
{
	void *p = NULL;
	p = malloc(1024);
	p = malloc(1024 * 32);
	p = malloc(1024 * 1024);
	p = malloc(1024 * 1024 * 16);
	p = malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}