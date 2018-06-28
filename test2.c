/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:36:40 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/28 15:38:48 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// #include "malloc.h"

int main() 
{ 
	int i; 
	char *addr; 
	(void)addr;
	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		free(addr);
		i++;
	}
	// show_alloc_mem();
	return (0); 
}
