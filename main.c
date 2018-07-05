/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 15:18:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/05 15:24:06 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char *p;

	// setenv("MallocScribble", "1", 1);

	// p = calloc(10, sizeof(char));
	p = malloc(10 * sizeof(char));

	for (int i = 0; i < 10; i++)
	{
		printf("%d: %d\n", i, p[i]);
	}

	// unsetenv("MallocScribble");
	return (0);
}