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

static void ft_printf_ls(long long int n, int *i)
{
	char	c;
	unsigned long long int num;

	num = (n < 0) ? -n : n;
	if (n < 0)
		*i += write(1, "-", 1);
	ft_printf_lu(num, i);
}

static int ft_printf_c(int n, char c)
{
	int i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
	return (i);
}

static int ft_signed_numlen(long long int n)
{
	int i;
	long long num;

	i = (n < 0) ? 1 : 0;
	if (n == 0)
		return (1);
	num = (n < 0) ? -n : n;
	while (num)
	{
		num /= 10;
		i++;
	}
	return (i);
}

int	ft_printf_sgnd(va_list ap, t_format *f_s)
{
	int num_len;
	long long int n;
	int i;

	i = 0;
	if (f_s->modifier == 'h' && f_s->modifier_second != 'h')
		n = (short)va_arg(ap, int);
	else if (f_s->modifier == 'h' && f_s->modifier_second == 'h')
		n = (char)va_arg(ap, int);
	else if (f_s->modifier == 'l' && f_s->modifier_second != 'l')
		n = va_arg(ap, long int);
	else if (f_s->modifier == 'l' && f_s->modifier_second == 'l')
		n = va_arg(ap, long long int);
	else
		n = va_arg(ap, int);
	num_len = ft_signed_numlen(n);//(f_s->flag == '+' || f_s->flag_second == '+') ? 1 + ft_signed_numlen(n) :
	if (f_s->flag == '-' || f_s->flag_second == '-')
	{
		if (f_s->flag == '+' || f_s->flag_second == '+')
			i += (n >= 0) ? write(1, "+", 1) : write(1, "-", 1);
		else if (f_s->flag == ' ' || f_s->flag_second == ' ')
			i += write(1, " ", 1);
		i += ft_printf_c(f_s->accuracy - num_len, '0');
		ft_printf_ls(n, &i);
		f_s->accuracy += (f_s->flag == '+' || f_s->flag_second == '+'
				|| f_s->flag == ' ' || f_s->flag_second == ' ') ? 1 : 0;
		num_len += (f_s->flag == '+' || f_s->flag_second == '+'
				|| f_s->flag == ' ' || f_s->flag_second == ' ') ? 1 : 0;
		i += ft_printf_c(f_s->width - ((num_len > f_s->accuracy) ? num_len : f_s->accuracy), ' ');
	}
	else if (f_s->flag == '+' || f_s->flag_second == '+')
	{

		i += (n >= 0) ? write(1, "+", 1) : write(1, "-", 1);
		if ((f_s->flag == '0' || f_s->flag_second == '0') && !f_s->accuracy)
			i += ft_printf_c(f_s->width - num_len, '0');
		if (f_s->accuracy)
			i += ft_printf_c(f_s->accuracy, '0');


	}

	return (i);
}
/*
** ' ' && '-'
** '+' && '-'
** '0' && ' '
** '0' && '+'
** '+' !gnored ' '
** '-' !gnored '0'
*/
int	ft_printf_num(va_list ap, t_format *f_s)
{
	int i;

	i = 0;
	if (f_s->conversion_type == 'd' || f_s->conversion_type == 'i')
		return (ft_printf_sgnd(ap, f_s));
//	ft_printf_lu(va_arg(ap, unsigned long), &i);


	return (i);
}