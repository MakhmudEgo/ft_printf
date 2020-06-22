/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 03:24:18 by mizola            #+#    #+#             */
/*   Updated: 2020/06/14 03:24:20 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
** ' ' && '-'
** '+' && '-'
** '0' && ' '
** '0' && '+'
** '+' !gnored ' '
** '-' !gnored '0'
*/

int			ft_printf_num(va_list ap, t_format *f_s)
{
	int i;

	i = 0;
	if (f_s->cnv_tp == 'd' || f_s->cnv_tp == 'i')
		return (ft_printf_sgnd(ap, f_s));
	else if (f_s->cnv_tp == 'u')
		return (ft_printf_usgnd(ap, f_s));
	return (i);
}
