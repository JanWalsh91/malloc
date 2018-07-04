/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:26:47 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 13:42:53 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <pthread.h>
# include <fcntl.h>
# include <time.h>
# include <sys/time.h>
# include "../libft/inc/libft.h"

# define EXPORT __attribute__ ((visibility("default")))
# define BLOCK_HEADER_SIZE (sizeof(struct s_block) - sizeof(int))
# define REGION_HEADER_SIZE (sizeof(struct s_region) - sizeof(size_t))
# define align4(x) (((((x)-1)>>2)<<2)+4)
# define TINY_LIMIT ((size_t)getpagesize() / 4)
# define SMALL_LIMIT (TINY_LIMIT * TINY_LIMIT)
# define TINY_MIN_MAP_SIZE (TINY_LIMIT * 200)
# define SMALL_MIN_MAP_SIZE (SMALL_LIMIT * 100)

typedef struct s_block	*t_block;

struct					s_block {
	size_t	size; // excludes header size
	t_block prev;
	t_block next;
	int		free;
	int		content;
};

typedef struct s_region	*t_region;

struct					s_region {
	size_t 			size; // includes header size
	t_region		next;
	t_region		prev;
	t_block			last_block;
	t_block			after_last_block;
	size_t			content;
};

typedef struct	s_lists
{
	t_region			tiny;
	t_region			small;
	t_region			large;
	const char*			names[3];
}				t_lists;

t_lists			g_lists;

pthread_mutex_t	mutex;

int				g_fd;

void		free(void *ptr) EXPORT;
void		*malloc(size_t size) EXPORT;
void		*realloc(void *ptr, size_t size) EXPORT;
void		show_alloc_mem(void) EXPORT;

void		*malloc_thread_unsafe(size_t size);
void		free_thread_unsafe(void *ptr);
void		*realloc_thread_unsafe(void *ptr, size_t size);
void		show_alloc_mem_thread_unsafe(void);

// global
void		init_lists(void);

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
void		unmap_all_regions(t_region region);
void		unmap_regions_recursively(t_region region);
size_t		get_region_min_map_size(size_t size);

// block
void		set_new_block(void *ptr, size_t size);
void		*get_block_content(t_block block);
void		link_blocks(t_block prev, t_block current);
void		unset_block(t_region region, t_block block);
int			can_split_block(t_block block, size_t size);
void		split_block(t_region region, t_block block, size_t size);

// print
void		print_region_list(t_region region, int i, size_t *total_size);
void		print_block(t_block block, size_t *total_size);
void		print_timestamp();

// helper functions
void		putbase(size_t n, size_t base) EXPORT;
void		putbase_fd(size_t n, size_t base, int fd);
void		print_mmap_error(void);
void		print_free_error(void *ptr);

// free
t_region	get_region_containing_pointer(void *ptr);
t_block		get_block_containing_pointer(t_region region, void *ptr);
void		defragment(t_region region, t_block block);
void		merge(t_region region, t_block block1, t_block block2);

// realloc


// scribble
void		scribble(t_block block, int value);

// log
void		malloc_log();

#endif