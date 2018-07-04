/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:00:58 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/28 16:11:58 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int main() 
{ 
	malloc(1024); 
	malloc(1024 * 32); 
	malloc(1024 * 1024); 
	malloc(1024 * 1024 * 16); 
	malloc(1024 * 1024 * 128); 
	show_alloc_mem(); 
	return (0); 
}
