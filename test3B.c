/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3B.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 13:36:40 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/28 15:50:49 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define M (1024 * 1024) 

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print(char *s) 
{ 
	write(1, s, strlen(s)); 
} 

int main() 
{ 
	char *addr1; 
	char *addr2; 
	char *addr3; 

	addr1 = (char*)malloc(16*M); 
	strcpy(addr1, "Bonjours\n"); 
	print(addr1); 
	addr2 = (char*)malloc(16*M); 
	addr3 = (char*)realloc(addr1, 128*M); 
	addr3[127*M] = 42; 
	print(addr3); 
	return (0); 
} 