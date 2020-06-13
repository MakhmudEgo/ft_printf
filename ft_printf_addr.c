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

static void	print_p(char c, unsigned long n, int *i)
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

int			ft_printf_addr(int c, va_list ap, char x)
{
	int i;

	i = 0;
	if ((char)c == 'p' || x)
		i += c == 'X' ? write(1, "0X", 2) : write(1, "0x", 2);
	if ((char)c == 'p')
		print_p((char)c, va_arg(ap, unsigned long), &i);
	else
		print_p((char)c, va_arg(ap, int), &i);
	return (i);
}
