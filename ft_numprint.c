/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:08:10 by mizola            #+#    #+#             */
/*   Updated: 2020/06/16 17:08:11 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_printf_unsigned(unsigned long n, int *i)
{
	char	c;

	if (n > 9)
		ft_printf_unsigned(n / 10, i);
	c = n % 10 + '0';
	*i += write(1, &c, 1);
}

void	ft_printf_signed(long long int n, int *i)
{
	char					c;
	unsigned long long int	num;

	num = (n < 0) ? -n : n;
	if (n < 0)
		*i += write(1, "-", 1);
	ft_printf_unsigned(num, i);
}
