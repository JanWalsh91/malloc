/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 17:53:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/07 16:53:14 by jwalsh           ###   ########.fr       */
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
# include <sys/time.h>
# include "../libft/inc/libft.h"

# define EXPORT __attribute__((visibility("default")))
# define BLOCK_HEADER_SIZE (32)
# define REGION_HEADER_SIZE (48)
# define TINY_LIMIT (1024)
# define SMALL_LIMIT (1048576)
// # define TINY_MIN_MAP_SIZE (204800)
# define TINY_MIN_MAP_SIZE (1024)
# define SMALL_MIN_MAP_SIZE (104857600)

# define malloc ft_malloc
# define free ft_free
# define realloc ft_realloc
# define show_alloc_mem ft_show_alloc_mem
# define calloc ft_calloc

typedef struct s_block	*t_block;

/*
** Block structure
** size excludes header size
*/

struct					s_block
{
	size_t			size;
	t_block			prev;
	t_block			next;
	size_t			free;
	int				content;
};

/*
** Region structure
** size includes header size
*/

typedef struct s_region	*t_region;

struct					s_region
{
	size_t			size;
	t_region		next;
	t_region		prev;
	t_block			last_block;
	t_block			after_last_block;
	size_t			padding;
	size_t			content;
};

typedef struct			s_lists
{
	t_region			tiny;
	t_region			small;
	t_region			large;
	const char			*names[3];
}						t_lists;

t_lists					g_lists;

pthread_mutex_t			g_mutex;

/*
** Lib export functions
** Wrappers for safe multithreading control (Bonus)
*/

void					*malloc(size_t size) EXPORT;
void					*calloc(size_t count, size_t size) EXPORT;
void					free(void *ptr) EXPORT;
void					*realloc(void *ptr, size_t size) EXPORT;
void					show_alloc_mem(void) EXPORT;

/*
** Wrapped functions for multithreading control (Bonus)
*/

void					*malloc_thread_unsafe(size_t size);
void					*calloc_thread_unsafe(size_t count, size_t size);
void					free_thread_unsafe(void *ptr);
void					*realloc_thread_unsafe(void *ptr, size_t size);
void					show_alloc_mem_thread_unsafe(void);

/*
** global
*/

void					init_lists(void);

/*
** region
*/

t_region				get_region_head(size_t size);
t_region				*get_first_region(size_t size);
t_region				get_new_region(size_t size);
int						region_has_space(t_region region, size_t size);
t_block					find_block_at_end_of_region(t_region region,
							size_t size);
t_block					find_block_in_freed_space(t_region region, size_t size);
t_block					get_block_from_new_region(t_region region, size_t size);
size_t					get_size_of_free_space_at_end_of_region(
							t_region region);
void					update_last_block_info(t_region region,
							t_block block);
void					link_regions(t_region prev, t_region current);
int						region_is_free(t_region region);
int						try_to_unmap_regions(t_region region);
void					unmap_region(t_region region);
void					unmap_all_regions(t_region region);
void					unmap_regions_recursively(t_region region);
size_t					get_region_min_map_size(size_t size);
t_region				get_region_containing_pointer(void *ptr);

/*
** Block
*/

void					set_new_block(void *ptr, size_t size);
void					*get_block_content(t_block block);
void					link_blocks(t_block prev, t_block current);
void					unset_block(t_region region, t_block block);
int						can_split_block(t_block block, size_t size);
void					split_block(t_region region, t_block block,
							size_t size);
t_block					get_block_containing_pointer(t_region region,
							void *ptr);

/*
** show_alloc_mem helper functions
*/

void					print_region_list(t_region region, int i,
							size_t *total_size);
void					print_block(t_block block, size_t *total_size);
void					putbase(size_t n, size_t base);

/*
** Error functions
*/

void					print_mmap_error(void);
void					print_free_error(void *ptr);

/*
** Defrag functions (Bonus)
*/

void					defragment(t_region region, t_block block);
void					merge_blocks(t_region region, t_block block1,
							t_block block2);

/*
** Scribble (Bonus)
*/

void					scribble(t_block block, int value);

/*
** Realloc helper function
*/

void					*malloc_and_free(t_block block, size_t size, void *ptr);

/*
** Align bytes
*/

size_t					align16(size_t n);

#endif
