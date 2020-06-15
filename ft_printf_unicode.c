/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unicode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:29:06 by mizola            #+#    #+#             */
/*   Updated: 2020/06/15 15:29:09 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int print_chars_2oct(const int src)
{
	int i;
	char oct_1;

	i = 0;
	oct_1 = (src >> 6) | 0b11000000;
	i += write(1, &oct_1, 1);
	oct_1 = (src & 0b00111111) | 0b10000000;
	i += write(1, &oct_1, 1);
	return (i);
}

static int print_chars_3oct(const int src)
{
	int i;
	char oct_1;

	i = 0;
	oct_1 = (src >> 12) | 0b11100000;
	i += write(1, &oct_1, 1);
	oct_1 = ((src >> 6) & 0b00000000111111) | 0b10000000;
	i += write(1, &oct_1, 1);
	oct_1 = (src & 0b00000000111111) | 0b10000000;
	i += write(1, &oct_1, 1);
	return (i);
}

static int print_chars_4oct(const int src)
{
	int i;
	char oct_1;

	i = 0;
	oct_1 = (src >> 18) | 0b11110000;
	i += write(1, &oct_1, 1);
	oct_1 = ((src >> 12) & 0b000000000000000111111) | 0b10000000;
	i += write(1, &oct_1, 1);
	oct_1 = ((src >> 6) & 0b000000000000000111111) | 0b10000000;
	i += write(1, &oct_1, 1);
	oct_1 = (src & 0b000000000000000111111) | 0b10000000;
	i += write(1, &oct_1, 1);
	return (i);
}


static int print_chars(int src)
{
	int i;
	int tmp;

	i = 0;
	tmp = src;
	while (tmp)
	{
		tmp >>= 1;
		i++;
	}
	if (i < 8)
		return (write(1, &src, 1));
	else if (i < 12)
		return (print_chars_2oct(src));
	else if (i < 17)
		return (print_chars_3oct(src));
	else if (i > 16)
		return (print_chars_4oct(src));
	return (i);
}

int ft_printf_unicode(va_list ap, char c_arg)
{
	int i;
	wchar_t *ptr_uni;

	ptr_uni = 0x0;
	i = 0;
	if (c_arg == 'c')
		return (print_chars(va_arg(ap, int)));
	else
	{
		ptr_uni = va_arg(ap, wchar_t*);
		while (*ptr_uni)
		{
			i += print_chars(*ptr_uni);
			ptr_uni++;
		}

	}
	return (i);
}
