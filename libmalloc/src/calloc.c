/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 15:16:03 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/09 16:20:46 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = NULL;
	pthread_mutex_lock(&g_mutex);
	init_lists();
	ptr = calloc_thread_unsafe(count, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void	*calloc_thread_unsafe(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc_thread_unsafe(count * size);
	ft_bzero(ptr, align(count * size));
	return (ptr);
}
