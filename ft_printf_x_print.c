/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 12:05:30 by mizola            #+#    #+#             */
/*   Updated: 2020/06/26 12:48:31 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	print_x(char c, unsigned int n, int *i)
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
	*i += write(1, &n_hex, 1);
}

void	print_lx(char c, unsigned long long n, int *i)
{
	char	n_hex;

	if (n >= 16)
		print_lx(c, n >> 4, i);
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
	*i += write(1, &n_hex, 1);
}
