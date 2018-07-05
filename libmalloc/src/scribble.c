/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scribble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:29:04 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/05 15:53:24 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	scribble(t_block block, int value)
{
	if (get_block_content(block))
		ft_memset(get_block_content(block), value, block->size);
}
