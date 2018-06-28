/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 11:21:37 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/28 14:53:42 by jwalsh           ###   ########.fr       */
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
		// abort();
	}
}
