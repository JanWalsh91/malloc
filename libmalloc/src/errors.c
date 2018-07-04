/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 11:21:37 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/30 13:59:37 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	print_mmap_error(void)
{
	ft_putstr("*** error: can't allocate region\n");
}

void	print_free_error(void *ptr)
{
	if (ptr)
	{
		ft_putstr("*** error for object 0x");
		putbase((size_t)(ptr), 16);
		ft_putstr(": pointer being freed was not allocated\n");
	}
}

void	print_thread_pid(void)
{
	// uint64_t tid;
 	// pthread_threadid_np(NULL, &tid);
	// ft_putnbr((int)tid);
	// ft_putchar('\n');
}
