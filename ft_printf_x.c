/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 21:56:14 by mizola            #+#    #+#             */
/*   Updated: 2020/06/25 22:13:41 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	print_x(char c, unsigned int n, int *i)
{
	char	n_hex;

	if (n >= 16)
		print_x(c, n >> 4, i);
	n_hex = (int)(n % 16) + '0';
	if ((int)n_hex == 58)
		n_hex = (c == 'X') ? 'A' : 'a';
	if ((int)n_hex == 59)
		n_hex = (c == 'X') ? 'B' : 'b';
	if ((int)n_hex == 60)
		n_hex = (c == 'X') ? 'C' : 'c';
	if ((int)n_hex == 61)
		n_hex = (c == 'X') ? 'D' : 'd';
	if ((int)n_hex == 62)
		n_hex = (c == 'X') ? 'E' : 'e';
	if ((int)n_hex == 63)
		n_hex = (c == 'X') ? 'F' : 'f';
	write(1, &n_hex, 1);
	*i += 1;
}

int ft_printf_x(va_list ap, t_format *f_s)
{
	int i;

	i = 0;
	if (f_s->mdf == 'h' && f_s->mdf_ii != 'h')
		print_x(f_s->cnv_tp, (unsigned short)va_arg(ap, int), &i);
	else if (f_s->mdf == 'h' && f_s->mdf_ii == 'h')
		print_x(f_s->cnv_tp, (unsigned char)va_arg(ap, int), &i);
	else
		print_x(f_s->cnv_tp, va_arg(ap, int), &i);
	return (i);
}
