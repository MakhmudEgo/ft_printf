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

static void	print_p(char c, unsigned long long n, int *i)
{
	char	n_hex;

	if (n >= 16)
		print_p(c, n >> 4, i);
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

static void	print_x(char c, unsigned int n, int *i, t_format *f_s)
{
	char	n_hex;

	if (n >= 16)
		print_x(c, n >> 4, i, f_s);
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

int			ft_printf_addr(char c, va_list ap, t_format *f_s)
{
	int i;

	i = 0;
	if (c == 'p' || f_s->modifier_x)
		i += c == 'X' ? write(1, "0X", 2) : write(1, "0x", 2);
	if (c == 'p' || f_s->modifier == 'l')
		print_p(c, va_arg(ap, unsigned long), &i);
	else
	{
		if (f_s->modifier == 'h' && f_s->modifier_second != 'h')
			print_x(c, (unsigned short)va_arg(ap, int), &i, f_s);
		else if (f_s->modifier == 'h' && f_s->modifier_second == 'h')
			print_x(c, (unsigned char)va_arg(ap, int), &i, f_s);
		else
			print_x(c, va_arg(ap, int), &i, f_s);
	}
	return (i);
}
