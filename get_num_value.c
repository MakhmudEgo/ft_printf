/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 00:51:42 by mizola            #+#    #+#             */
/*   Updated: 2020/06/17 00:53:14 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

long long int	get_num_value(va_list ap, t_format *f_s)
{
	long long int	n;

	if (f_s->mdf == 'h' && f_s->mdf_ii != 'h')
		n = (short)va_arg(ap, int);
	else if (f_s->mdf == 'h' && f_s->mdf_ii == 'h')
		n = (char)va_arg(ap, int);
	else if (f_s->mdf == 'l' && f_s->mdf_ii != 'l')
		n = va_arg(ap, long int);
	else if (f_s->mdf == 'l' && f_s->mdf_ii == 'l')
		n = va_arg(ap, long long int);
	else
		n = va_arg(ap, int);
	return (n);
}