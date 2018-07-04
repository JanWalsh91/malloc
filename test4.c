/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/29 17:04:17 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define M (1024 * 1024)

void print(char *s) 
{ 
	write(1, s, strlen(s)); 
} 

int main() 
{ 
	char *addr; 

	addr = malloc(16); 
	free(NULL); 
	free((void *)addr + 5); 
	if (realloc((void *)addr + 5, 10) == NULL) 
		print("Bonjours\n"); 
} 