/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_sgnd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 17:11:33 by mizola            #+#    #+#             */
/*   Updated: 2020/06/16 17:11:34 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	if_minus(const long long int *n, t_format *f_s,
		int *num_len, int *i)
{
	*i += (*n < 0) ? write(1, "-", 1) : 0;
	if (f_s->flg == '+' || f_s->flg_ii == '+')
		*i += (*n >= 0) ? write(1, "+", 1) : 0;
	else if (f_s->flg == ' ' || f_s->flg_ii == ' ')
		*i += write(1, " ", 1);
	*i += ft_printf_char(f_s->acc - (*n < 0 ? (*num_len - 1)
			: *num_len), '0');
	ft_printf_signed(((*n < 0) ? -(*n) : *n), i);
	f_s->acc += (f_s->flg == '+' || f_s->flg_ii == '+'
			|| f_s->flg == ' ' || f_s->flg_ii == ' ' || (*n < 0)) ? 1 : 0;
	*num_len += (*n > 0) && (f_s->flg == '+' || f_s->flg_ii == '+'
				|| f_s->flg == ' ' || f_s->flg_ii == ' ') ? 1 : 0;
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

void	if_plus(long long int *n, t_format *f_s,
		int *num_len, int *i)
{
	if ((f_s->flg == '0' || f_s->flg_ii == '0') && f_s->acc != -1)
	{
		*i += write(1, (*n >= 0) ? "+" : "-", 1);
		*i += ft_printf_char(f_s->wdth - (*num_len), '0');
	}
	else
	{
		*i += ft_printf_char(f_s->wdth - ((f_s->acc < *num_len) ?
				*num_len + 1 : f_s->acc + 1), ' ');
		*i += write(1, (*n >= 0) ? "+" : "-", 1);
		*i += ft_printf_char(f_s->acc - (*num_len - 1), '0');
	}
	ft_printf_signed((*n < 0) ? -(*n) : *n, i);
}

void	if_space(long long int *n, t_format *f_s,
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
	ft_printf_signed((*n < 0) ? -(*n) : *n, i);
}

void	if_else(long long int *n, t_format *f_s,
		int *num_len, int *i)
{
	*i += (*n < 0) ? write(1, "-", 1) : 0;
	f_s->acc += f_s->acc && (f_s->flg == '+'
			|| f_s->flg_ii == '+' || f_s->flg == ' '
			|| f_s->flg_ii == ' ' || (*n < 0)) ? 1 : 0;
	*num_len += (f_s->flg == '+' || f_s->flg_ii == '+'
			|| f_s->flg == ' ' || f_s->flg_ii == ' ') ? 1 : 0;
	if (f_s->flg == '0' || f_s->flg_ii == '0')
	{
		if (f_s->acc)
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
	ft_printf_signed((*n < 0) ? -(*n) : *n, i);
}

int		ft_printf_sgnd(va_list ap, t_format *f_s)
{
	int				num_len;
	long long int	n;
	int				i;

	i = 0;
	n = get_num_value(ap, f_s);
	num_len = ft_signed_numlen(n);
	if (f_s->flg == '-' || f_s->flg_ii == '-')
		if_minus(&n, f_s, &num_len, &i);
	else if (f_s->flg == '+' || f_s->flg_ii == '+')
	{
		num_len += (n >= 0) && (f_s->flg == '+' || f_s->flg_ii == '+') ? 1 : 0;
		if_plus(&n, f_s, &num_len, &i);
	}
	else if ((f_s->flg == ' ' || f_s->flg_ii == ' ') && (n >= 0))
	{
		num_len += (n >= 0) && (f_s->flg == '+' || f_s->flg_ii == '+') ? 1 : 0;
		if_space(&n, f_s, &num_len, &i);
	}
	else
		if_else(&n, f_s, &num_len, &i);
	return (i);
}
