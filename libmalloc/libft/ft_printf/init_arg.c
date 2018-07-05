/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 12:27:10 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/05 14:00:48 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Sets default values for the arg structure.
** Note: precision set to -1 translates to precision being ignored.
*/

int			init_arg(t_arg *arg)
{
	arg->result_len = 0;
	set_default_flags(&arg->flags);
	arg->width = 0;
	arg->precision = -1;
	arg->length = 0;
	arg->type = 0;
	arg->neg_int = 0;
	arg->null_char = 0;
	return (1);
}

void		set_default_flags(t_flags *flags)
{
	flags->hashtag = 0;
	flags->zero = 0;
	flags->minus = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->single_quote = 0;
}
