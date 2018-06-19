/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:36:40 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/19 13:54:44 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	main(void)
{
	char *addr;

	addr = (char*)malloc(10);
	show_alloc_mem();
	
	free(addr);
	addr = (char*)malloc(20);
	show_alloc_mem();

	free(addr);
	show_alloc_mem();

	addr = (char*)malloc(10);
	show_alloc_mem();

	return (0);
}