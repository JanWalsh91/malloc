/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testTMP.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/09 13:32:20 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>

int main() 
{ 
	int i; 
	char *addr; 
	(void)addr;
	i = 0; 
	while (i < 1)
	{
		addr = (char*)ft_malloc(1024);
		free(addr);
		// addr[0] = 42; 
		printf("\n\nvalue: %d\n", addr[0]);
		i++; 
	}
	return (0); 
} 