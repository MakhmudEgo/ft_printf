/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_sgnd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:11:33 by mizola            #+#    #+#             */
/*   Updated: 2020/06/27 13:09:39 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	if_minus(long long int *n, t_format *f_s,
		int *num_len, int *i)
{
	*i += *n < 0 ? write(1, "-", 1) : 0;
	*i += *n >= 0 && f_s->is_spc && !f_s->is_pls ? write(1, " ", 1) : 0;
	*i += *n >= 0 && (f_s->is_pls) ? write(1, "+", 1) : 0;
	*i += f_s->acc != -1 && *n >= 0 ? ft_printf_char(f_s->acc - *num_len, '0') : 0;
	*i += f_s->acc != -1 && *n < 0 ? ft_printf_char(f_s->acc - *num_len + 1, '0') : 0;
	ft_print_check_zero(n, f_s, i);
	f_s->acc += *n < 0 && f_s->acc != -1 ? 1 : 0;
	f_s->acc += *n >= 0 && (f_s->is_spc || f_s->is_pls) ? 1 : 0;
	*num_len += f_s->is_pls && *n >= 0 ? 1 : 0;
	*i += f_s->acc > *num_len ? ft_printf_char(f_s->wdth - f_s->acc, ' ') :
			ft_printf_char(f_s->wdth - *num_len, ' ');
}

/*
** ' ' && '-'
** '+' && '-'
** '0' && ' '
** '0' && '+'
** '+' !gnored ' '
** '-' !gnored '0'
** acc !gnored '0'
*/

static void	if_plus(long long int *n, t_format *f_s,
		int *num_len, int *i)
{
	if (f_s->is_zr && f_s->acc == -1)
	{
		*i += write(1, (*n >= 0) ? "+" : "-", 1);
		*i += ft_printf_char(f_s->wdth - (*num_len), '0');
	}
	else
	{
		*i += ft_printf_char(f_s->wdth - ((f_s->acc < *num_len) ?
				*num_len : f_s->acc + 1), ' ');
		*i += write(1, (*n >= 0) ? "+" : "-", 1);
		*i += ft_printf_char(f_s->acc - (*num_len - 1), '0');
	}
	ft_print_check_zero(n, f_s, i);
}

static void	if_space(long long int *n, t_format *f_s,
		int *num_len, int *i)
{

	ft_print_check_zero(n, f_s, i);
}

static void	if_else(long long int *n, t_format *f_s,
		int *num_len, int *i)
{
	f_s->acc += *n < 0 && f_s->acc != -1 ? 1 : 0;
	if (f_s->is_zr && f_s->acc == -1)
	{
		*i += *n < 0 ? write(1, "-", 1) : 0;
		*i += *num_len > f_s->acc ? ft_printf_char(f_s->wdth - *num_len, '0') :
				ft_printf_char(f_s->wdth - f_s->acc, '0');
	}
	else
	{
		*i += *num_len > f_s->acc ? ft_printf_char(f_s->wdth - *num_len, ' ') :
				ft_printf_char(f_s->wdth - f_s->acc, ' ');
		*i += *n < 0 ? write(1, "-", 1) : 0;
	}
	*i += ft_printf_char(f_s->acc - (*num_len), '0');
	ft_print_check_zero(n, f_s, i);
}

int			ft_printf_sgnd(va_list ap, t_format *f_s)
{
	int				num_len;
	long long int	n;
	int				i;

	i = 0;
	n = get_sngd_value(ap, f_s);
	num_len = ft_signed_numlen(n);
	if (f_s->is_mns)
		if_minus(&n, f_s, &num_len, &i);
	else if (f_s->is_pls)
	{
		num_len += n >= 0 && f_s->is_pls ? 1 : 0;
		if_plus(&n, f_s, &num_len, &i);
	}
	else if (f_s->is_spc)
	{
		if_space(&n, f_s, &num_len, &i);
	}
	else
		if_else(&n, f_s, &num_len, &i);
	return (i);
}
