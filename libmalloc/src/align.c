/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   align.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 13:39:47 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/09 16:34:50 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t	align(size_t n)
{
	size_t	diff;
	size_t	alignment;

	alignment = ALIGNMENT;
	if (alignment % 4 != 0)
		alignment = 16;
	diff = n % alignment;
	if (diff == 0 && n != 0)
		return (n);
	return (n - diff + alignment);
}
