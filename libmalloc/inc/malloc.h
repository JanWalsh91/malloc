/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:26:47 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/11 16:06:40 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define BLOCK_SIZE sizeof(struct block_s)
# define REGION_SIZE sizeof(struct region_s)
// block for a single malloc allocation
typedef struct block_s	*block_t;

struct					block_s {
	int		used;
	// size of content or block total ?
	size_t	size;
	struct block_s *next;
	
	char data[1];
	// char	tab[0]; // content ptr. or tab[1] to have pointer and space for one byte.
	// char	content; // content ptr // leave at end
};

// region allocated by mmap
typedef struct region_s	*region_t;

struct					region_s {
	// number of pages in region
	size_t			nb_pages;
	// pointer to first block
	block_t			*blocks;
	// total allocated size or available size ?
	size_t 			total_size;
	// pointer to next region
	struct region_s	*next;
};

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
// void		show_alloc_mem();

// region
region_t	*get_first_region();
region_t	get_next_available_region(size_t size);
region_t	get_new_region(size_t size);

// block
block_t get_new_block(size_t size);
block_t get_next_available_block(size_t size);

#endif