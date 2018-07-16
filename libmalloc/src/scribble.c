/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scribble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:29:04 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/09 15:35:39 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	scribble(t_block block, int value)
{
	if (SCRIBBLE && get_block_content(block))
		ft_memset(get_block_content(block), value, block->size);
}
