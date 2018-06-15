/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:26:47 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/15 12:28:14 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define BLOCK_SIZE sizeof(struct s_block)
# define REGION_SIZE sizeof(struct s_region)
// block for a single malloc allocation
typedef struct s_block	*t_block;

struct					s_block {
	int		used;
	// size of content or block total ?
	size_t	size;
	t_block next;
	
	char	content[1];
	// char	tab[0]; // content ptr. or tab[1] to have pointer and space for one byte.
	// char	content; // content ptr // leave at end
};

// region allocated by mmap
typedef struct s_region	*t_region;

struct					s_region {
	// number of pages in region
	size_t			nb_pages;
	
	// total allocated size or available size ?
	size_t 			total_size;
	// pointer to next region
	t_region		next;
	// size of largest free space
	size_t			largest_free_space;
	// location of first block
	char			content[1];
};

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
// void		show_alloc_mem();

// region
t_region	*get_first_region();
t_region	get_next_available_region(size_t size);
t_region	get_new_region(size_t size);

// block
void	 set_new_block(void* ptr, size_t size);
t_block get_next_available_block_in_region(t_region region, size_t size);

#endif