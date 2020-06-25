/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_usgnd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 19:55:24 by mizola            #+#    #+#             */
/*   Updated: 2020/06/25 21:09:36 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	if_minus(unsigned long long *n, t_format *f_s,
		int *num_len, int *i)
{
	*i += ft_printf_char(f_s->acc - *num_len, '0');
	ft_print_check_uzero(n, f_s, i);
	*i += ft_printf_char(f_s->wdth - ((*num_len > f_s->acc) ?
			*num_len : f_s->acc), ' ');
}

/*
** ' ' && '-'
** '+' && '-'
** '0' && ' '
** '0' && '+'
** '+' !gnored ' '
** '-' !gnored '0'
*/

static void	if_plus(unsigned long long *n, t_format *f_s,
		int *num_len, int *i)
{
	if ((f_s->flg == '0' || f_s->flg_ii == '0') && f_s->acc == -1)
		*i += ft_printf_char(f_s->wdth - (*num_len), '0');
	else
	{
		*i += ft_printf_char(f_s->wdth - ((f_s->acc < *num_len) ?
				*num_len : f_s->acc), ' ');
		*i += ft_printf_char(f_s->acc - (*num_len), '0');
	}
	ft_print_check_uzero(n, f_s, i);
}

static void	if_space(unsigned long long *n, t_format *f_s,
		int *num_len, int *i)
{
	*i += write(1, " ", 1);
	*i += f_s->acc == -1 && (f_s->flg == '0' || f_s->flg_ii == '0') ?
			ft_printf_char(f_s->wdth - *num_len - 1, '0') : 0;
	*i += f_s->acc != -1 && f_s->acc > *num_len ?
			ft_printf_char(f_s->wdth - f_s->acc - 1, ' ') : 0;
	*i += f_s->acc != -1 && f_s->acc < *num_len ?
			ft_printf_char(f_s->wdth - *num_len - 1, ' ') : 0;
	*i += f_s->acc == -1 && (f_s->flg != '0' && f_s->flg_ii != '0') ?
			ft_printf_char(f_s->wdth - *num_len - 1, ' ') : 0;
	*i += f_s->acc != -1 ? ft_printf_char(f_s->acc - *num_len, '0') : 0;
	ft_print_check_uzero(n, f_s, i);
}

static void	if_else(unsigned long long *n, t_format *f_s,
		int *num_len, int *i)
{
	if (f_s->flg == '0' || f_s->flg_ii == '0')
	{
		if (f_s->acc != -1)
		{
			*i += ft_printf_char(f_s->wdth - ((f_s->acc < *num_len)
				? (*num_len) : f_s->acc), ' ');
			*i += ft_printf_char(f_s->acc - (*num_len), '0');
		}
		else
			i += ft_printf_char(f_s->wdth - (*num_len), '0');
	}
	else
	{
		*i += ft_printf_char(f_s->wdth - ((f_s->acc < *num_len)
			? (*num_len) : f_s->acc), ' ');
		*i += ft_printf_char(f_s->acc - (*num_len), '0');
	}
	ft_print_check_uzero(n, f_s, i);
}

int			ft_printf_usgnd(va_list ap, t_format *f_s)
{
	int					num_len;
	unsigned long long	n;
	int					i;

	i = 0;
	n = get_usgnd_value(ap, f_s);
	num_len = ft_unsigned_numlen(n);
	if (f_s->flg == '-' || f_s->flg_ii == '-')
		if_minus(&n, f_s, &num_len, &i);
	else if (f_s->flg == '+' || f_s->flg_ii == '+')
		if_plus(&n, f_s, &num_len, &i);
	else if ((f_s->flg == ' ' || f_s->flg_ii == ' '))
		if_space(&n, f_s, &num_len, &i);
	else
		if_else(&n, f_s, &num_len, &i);
	return (i);
}
