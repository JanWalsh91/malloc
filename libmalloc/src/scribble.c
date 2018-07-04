/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scribble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:29:04 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 12:32:15 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	scribble(t_block block, int value)
{
	ft_putstr("scribble:\n");
	if (getenv("MALLOC_SCRIBBLE"))
	{
		ft_putstr("scribbling ");
		putbase((size_t)get_block_content(block), 16);
		ft_putstr(" !\n");
		if (get_block_content(block))
			ft_memset(get_block_content(block), value, block->size);
	}
}
