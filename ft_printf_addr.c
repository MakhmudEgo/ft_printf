/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 02:08:04 by mizola            #+#    #+#             */
/*   Updated: 2020/06/04 02:08:05 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	print_p(unsigned long i)
{
	char n_hex;

	if (i >= 16)
		print_p(i/16);

	n_hex = (int)(i % 16) + '0';
	if ((int)n_hex == 58)
		n_hex = 'a';
	if ((int)n_hex == 59)
		n_hex = 'b';
	if ((int)n_hex == 60)
		n_hex = 'c';
	if ((int)n_hex == 61)
		n_hex = 'd';
	if ((int)n_hex == 62)
		n_hex = 'e';
	if ((int)n_hex == 63)
		n_hex = 'f';
	write(1, &n_hex, 1);
	return 0;
}

int ft_printf_addr(int c, ...)
{
	va_list ap;

	va_start(ap, c);
	if (c == 'p') {
		print_p(va_arg(ap, unsigned long));
	}
	else {
		print_p(va_arg(ap, int));
	}
	return 0;
}