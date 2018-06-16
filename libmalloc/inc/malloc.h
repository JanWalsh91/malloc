/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:26:47 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/16 14:27:52 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/inc/libft.h"

# define BLOCK_HEADER_SIZE (sizeof(struct s_block) - 4)
# define REGION_HEADER_SIZE (sizeof(struct s_region) - 8)
# define align4(x) (((((x)-1)>>2)<<2)+4)
# define TINY_LIMIT 512
# define SMALL_LIMIT 4096
# define LIST_NAMES (const char**){"TINY", "SMALL", "LARGE"}
// block for a single malloc allocation
typedef struct s_block	*t_block;

struct					s_block {
	// size of content
	size_t	size;
	t_block prev;
	t_block next;
	int		free;
	int		content;
	// char	tab[0]; // content ptr. or tab[1] to have pointer and space for one byte.
	// char	content; // content ptr // leave at end
};

// region allocated by mmap
typedef struct s_region	*t_region;

struct					s_region {
	// number of pages in region. necessary?
	size_t			nb_pages;
	// total allocated size or available size ?
	size_t 			size;
	// pointer to next region
	t_region		next;
	// size of largest free space
	size_t			largest_free_space;
	size_t			space_at_end;
	// location of first block
	size_t				content;
};

typedef struct	s_lists
{
	t_region			tiny;
	t_region			small;
	t_region			large;
	size_t				total_size;
	const char*			names[3];
}				t_lists;

t_lists			g_lists;

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		show_alloc_mem();

// global
void		init_lists();

// region
t_region	*get_first_region(size_t size);
t_region	get_next_available_region(size_t size);
t_region	get_new_region(size_t size);
t_block		get_next_available_block_in_region(t_region region, size_t size);
void		update_region_header(t_region region, size_t size);

// block
void		set_new_block(void *ptr, size_t size);
// t_block	 	add_new_block(t_block block, t_region region, size_t size);
void		*get_block_content(t_block block);
void		link_blocks(t_block prev, t_block current);

// print
void		print_region(t_region region, int i);
void		print_block(t_block block);

// helper functions
void		putbase(size_t n, size_t base);

#endif