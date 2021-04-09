/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 00:51:42 by mizola            #+#    #+#             */
/*   Updated: 2020/06/27 16:31:30 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

long long int	get_sngd_value(va_list ap, t_format *f_s)
{
	long long int	n;

	if (f_s->mdf == 'h' && f_s->mdf_ii != 'h')
		n = (short)va_arg(ap, int);
	else if (f_s->mdf == 'h' && f_s->mdf_ii == 'h')
		n = (char)va_arg(ap, int);
	else if (f_s->mdf == 'l' && f_s->mdf_ii != 'l')
		n = (long int)va_arg(ap, long int);
	else if (f_s->mdf == 'l' && f_s->mdf_ii == 'l')
		n = va_arg(ap, long long);
	else
		n = va_arg(ap, int);
	return (n);
}

unsigned long long	get_usgnd_value(va_list ap, t_format *f_s)
{
	unsigned long long n;

	if (f_s->mdf == 'h' && f_s->mdf_ii != 'h')
		n = (unsigned short)va_arg(ap, int);
	else if (f_s->mdf == 'h' && f_s->mdf_ii == 'h')
		n = (unsigned char)va_arg(ap, int);
	else if (f_s->mdf == 'l' && f_s->mdf_ii != 'l')
		n = (unsigned long)va_arg(ap, unsigned long);
	else if (f_s->mdf == 'l' && f_s->mdf_ii == 'l')
		n = va_arg(ap, unsigned long long);
	else
		n = (unsigned int)(va_arg(ap, int));
	return (n);
}
