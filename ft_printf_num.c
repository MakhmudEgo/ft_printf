/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 03:24:18 by mizola            #+#    #+#             */
/*   Updated: 2020/06/14 03:24:20 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void ft_printf_lu(unsigned long n, int *i)
{
	char	c;

	if (n > 9)
		ft_printf_lu(n / 10, i);
	c = n % 10 + '0';
	*i += write(1, &c, 1);
}

int	ft_printf_num(va_list ap, t_format *f_s)
{
	int i;

	i = 0;
	ft_printf_lu(va_arg(ap, unsigned long), &i);


	return 0;
}