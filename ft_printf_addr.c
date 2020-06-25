/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 02:08:04 by mizola            #+#    #+#             */
/*   Updated: 2020/06/25 22:13:41 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	print_p(unsigned long long n, int *i)
{
	char	n_hex;

	if (n >= 16)
		print_p(n >> 4, i);
	n_hex = (int)(n % 16) + '0';
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
	*i += 1;
}

static int	ft_hex(unsigned long long n, t_format *f_s)
{
	int i;
	int hex_len;
	unsigned long long num;

	i = 0;
	num = n;
	hex_len = n == 0 ? 3 : 2;
	while (num)
	{
		num >>= 4;
		hex_len++;
	}
	if (f_s->flg == '-' || f_s->flg_ii == '-')
	{
		i += write(1, "0x", 2);
		print_p(n, &i);
	}
	i += ft_printf_char(f_s->wdth - hex_len, ' ');
	if (f_s->flg != '-' && f_s->flg_ii != '-')
	{
		i += write(1, "0x", 2);
		print_p(n, &i);
	}
	return (i);
}

int			ft_printf_addr(va_list ap, t_format *f_s)
{
	int i;

	i = 0;
	i += ft_hex(va_arg(ap, unsigned long), f_s);
	return (i);
}
