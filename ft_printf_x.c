/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 21:56:14 by mizola            #+#    #+#             */
/*   Updated: 2020/06/26 13:10:36 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	ft_hex(unsigned long long n, t_format *f_s)
{
	int					i;
	int					hex_len;
	unsigned long long	tmp_hex;

	i = 0;
	hex_len = n == 0 ? 1 : 0;
	hex_len += f_s->mdf_x == '#' ? 2 : 0;
	tmp_hex = f_s->mdf == 'l' ? n : (int)n;
	while (tmp_hex)
	{
		tmp_hex >>= 4;
		hex_len++;
	}
	if (f_s->flg == '-' || f_s->flg_ii == '-')
		if_minus_x(&n, f_s, &hex_len, &i);
	else if (f_s->flg == '+' || f_s->flg_ii == '+')
		if_plus_x(&n, f_s, &hex_len, &i);
	else if ((f_s->flg == ' ' || f_s->flg_ii == ' '))
		if_space_x(&n, f_s, &hex_len, &i);
	else
		if_else_x(&n, f_s, &hex_len, &i);
	return (i);
}

int			ft_printf_x(va_list ap, t_format *f_s)
{
	int i;

	i = 0;
	if (f_s->mdf == 'h' && f_s->mdf_ii != 'h')
		i += ft_hex((unsigned short)va_arg(ap, int), f_s);
	else if (f_s->mdf == 'h' && f_s->mdf_ii == 'h')
		i += ft_hex((unsigned char)va_arg(ap, int), f_s);
	else if (f_s->mdf == 'l')
		i += ft_hex(va_arg(ap, unsigned long long), f_s);
	else
		i += ft_hex(va_arg(ap, int), f_s);
	return (i);
}
