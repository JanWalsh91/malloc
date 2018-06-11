/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 15:59:10 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/11 16:04:42 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

block_t get_new_block(size_t size) {
	(void)size;
	block_t block;

	block->size = size;
	block->next = NULL;
	block->used = 1;
	return block;
}

block_t get_next_available_block(size_t size) {
	(void)size;
}