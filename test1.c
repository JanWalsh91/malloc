/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:36:40 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/09 13:29:05 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int main() 
{ 
	int i; 
	char *addr; 
	(void)addr;
	i = 0; 
	while (i < 1)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42; 
		
		i++; 
	}
	return (0); 
} 