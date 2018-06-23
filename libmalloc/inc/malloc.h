/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:26:47 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/23 13:44:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h> 
# include "../libft/inc/libft.h"

# define EXPORT __attribute__ ((visibility("default")))
# define BLOCK_HEADER_SIZE (sizeof(struct s_block) - sizeof(int))
# define REGION_HEADER_SIZE (sizeof(struct s_region) - sizeof(size_t))
# define align4(x) (((((x)-1)>>2)<<2)+4)
# define TINY_LIMIT (size_t)getpagesize()
# define SMALL_LIMIT (TINY_LIMIT * TINY_LIMIT)
# define TINY_MIN_MAP_SIZE (TINY_LIMIT * 200)
# define SMALL_MIN_MAP_SIZE (SMALL_LIMIT * 100)

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
	// total allocated size
	size_t 			size;
	// pointer to next region
	t_region		next;
	// pointer to prev region
	t_region		prev;
	// pointer to last block
	t_block			last_block;
	t_block			after_last_block;
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

void		free(void *ptr) EXPORT;
void		*malloc(size_t size) EXPORT;
void		*realloc(void *ptr, size_t size) EXPORT;
void		show_alloc_mem() EXPORT;

// global
void		init_lists();

// region
t_region	get_region_head(size_t size);
t_region	*get_first_region(size_t size);
t_region	get_new_region(size_t size);
int			region_has_space(t_region region, size_t size);
t_block		find_block_at_end_of_region(t_region region, size_t size);
t_block		find_block_in_freed_space(t_region region, size_t size);
t_block		get_block_from_new_region(t_region region, size_t size);
size_t		get_size_of_free_space_at_end_of_region(t_region region);
void		update_last_block_info(t_region region, t_block block);
void		link_regions(t_region prev, t_region current);
int			region_is_free(t_region region);
void		try_to_unmap_regions(t_region region);
void		unmap_region(t_region region);
size_t		get_region_min_map_size(size_t size);

// block
void		set_new_block(void *ptr, size_t size);
void		*get_block_content(t_block block);
void		link_blocks(t_block prev, t_block current);
void		unset_block(t_region region, t_block block);

// print
void		print_region_list(t_region region, int i);
void		print_block(t_block block);

// helper functions
void		putbase(size_t n, size_t base);
void		print_mmap_error(void);

// free
t_region	get_region_containing_pointer(void *ptr);
t_block		get_block_containing_pointer(t_region region, void *ptr);
void		defragment(t_region region, t_block block);
void		merge(t_region region, t_block block1, t_block block2);

// realloc
void		split_block(t_region region, t_block block, size_t size);

#endif