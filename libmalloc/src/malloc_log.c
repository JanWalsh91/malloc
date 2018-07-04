/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:57:13 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/04 13:37:25 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	malloc_log()
{
	const char	*path;

	ft_putstr("malloc_log:\n");
	if (getenv("MALLOC_LOG"))
	{
		path = getenv("MALLOC_LOG_FILE") ?
			getenv("MALLOC_LOG_FILE") : "malloc_log.txt";
		g_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IXUSR);
		if (g_fd < 0) {
			ft_putstr_fd("error opening file\n", 1);
			ft_putstr_fd(strerror(errno), 1);
			g_fd = 1;
		}
		else
			show_alloc_mem_thread_unsafe();
		
		if (close(g_fd))
			ft_putstr_fd("error closing file\n", 1);
		g_fd = 1;
	}
}
