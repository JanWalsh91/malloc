/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putbase.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 11:09:11 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 13:23:09 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	putbase(size_t n, size_t base)
{
	if (n > base - 1)
	{
		putbase(n / base, base);
		putbase(n % base, base);
	}
	else
	{
		if (n < 10)
			ft_putchar(n + '0');
		else
			ft_putchar(n + 'A' - 10);
	}
}

void	putbase_fd(size_t n, size_t base, int fd)
{
	if (n > base - 1)
	{
		putbase_fd(n / base, base, fd);
		putbase_fd(n % base, base, fd);
	}
	else
	{
		if (n < 10)
			ft_putchar_fd(n + '0', fd);
		else
			ft_putchar_fd(n + 'A' - 10, fd);
	}
}
