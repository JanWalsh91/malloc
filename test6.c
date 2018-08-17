/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/17 16:19:19 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <malloc.h>

void *x_malloc(void *ptr)
{
	void *p = NULL;
	(void)ptr;
	
	p = ft_malloc(500);
	p = ft_realloc(p, 100);
	ft_free(p);
	ft_show_alloc_mem();
	return NULL;
}

int main()
{
	pthread_t inc_x_thread[50];
	int y = 10;
	
	for (int i = 0; i < y; ++i) {
		if (pthread_create(&inc_x_thread[i], NULL, x_malloc, NULL))
		{
			printf("error creating thread\n");
			return 1;
		}
	}
	
	for (int i = 0; i < y; ++i)
	{
		if (pthread_join(inc_x_thread[i], NULL))
		{
			printf("Error joining thread\n");
			return 2;
		}
	}
	
	ft_show_alloc_mem();
	return (0);
}
