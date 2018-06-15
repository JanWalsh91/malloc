/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:18:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/06/15 12:32:55 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int	main(int ac, char** av)
{
	(void)ac;
	(void)av;
	char *ptr = NULL;
	ptr = (char *)malloc(5000);
	printf("done with malloc: %p\n", ptr);
	ptr[0] = 'A';
	printf("result: %c\n", ptr[0]);
	return (0);
}