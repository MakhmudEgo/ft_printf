/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x_assist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 11:54:39 by mizola            #+#    #+#             */
/*   Updated: 2020/06/27 17:38:29 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	if_minus_x(void *n, t_format *f_s,
		int *hex_len, int *i)
{
	check_pr(i, f_s, n);
	*i += ft_printf_char(f_s->acc - *hex_len, '0');
	if (f_s->mdf == 'l')
		ft_print_check_lxzero(n, f_s, i);
	else
		ft_print_check_xzero((unsigned int*)n, f_s, i);
	*i += ft_printf_char(f_s->wdth - ((*hex_len > f_s->acc) ?
			*hex_len : f_s->acc), ' ');
}

/*
** ' ' && '-'
** '+' && '-'
** '0' && ' '
** '0' && '+'
** '+' !gnored ' '
** '-' !gnored '0'
*/

void	if_plus_x(void *n, t_format *f_s,
		int *hex_len, int *i)
{
	if (f_s->is_zr && f_s->acc == -1)
	{
		check_pr(i, f_s, n);
		*i += ft_printf_char(f_s->wdth - (*hex_len), '0');
	}
	else
	{
		*i += ft_printf_char(f_s->wdth - ((f_s->acc < *hex_len) ?
				*hex_len : f_s->acc), ' ');
		check_pr(i, f_s, n);
		*i += ft_printf_char(f_s->acc - (*hex_len), '0');
	}
	if (f_s->mdf == 'l')
		ft_print_check_lxzero(n, f_s, i);
	else
		ft_print_check_xzero((unsigned int*)n, f_s, i);
}

void	if_space_x(void *n, t_format *f_s,
						int *hex_len, int *i)
{
	*i += write(1, " ", 1);
	if (f_s->acc == -1 && f_s->is_zr)
	{
		check_pr(i, f_s, n);
	}
	*i += f_s->acc == -1 && f_s->is_zr ?
			ft_printf_char(f_s->wdth - *hex_len - 1, '0') : 0;
	*i += f_s->acc != -1 && f_s->acc > *hex_len ?
			ft_printf_char(f_s->wdth - f_s->acc - 1, ' ') : 0;
	*i += f_s->acc != -1 && f_s->acc < *hex_len ?
			ft_printf_char(f_s->wdth - *hex_len - 1, ' ') : 0;
	*i += f_s->acc == -1 && !f_s->is_zr ?
			ft_printf_char(f_s->wdth - *hex_len - 1, ' ') : 0;
	if (f_s->acc != -1)
	{
		check_pr(i, f_s, n);
	}
	*i += f_s->acc != -1 ? ft_printf_char(f_s->acc - *hex_len, '0') : 0;
	if (f_s->mdf == 'l')
		ft_print_check_lxzero(n, f_s, i);
	else
		ft_print_check_xzero((unsigned int*)n, f_s, i);
}

void	if_zero_x(void *n, t_format *f_s,
		int *hex_len, int *i)
{
	if (f_s->acc != -1)
	{
		*i += ft_printf_char(f_s->wdth - ((f_s->acc < *hex_len)
				? (*hex_len) : f_s->acc), ' ');
		check_pr(i, f_s, n);
		*i += ft_printf_char(f_s->acc - (*hex_len), '0');
	}
	else
	{
		check_pr(i, f_s, n);
		*i += ft_printf_char(f_s->wdth - (*hex_len), '0');
	}
	if (f_s->mdf == 'l')
		ft_print_check_lxzero(n, f_s, i);
	else
		ft_print_check_xzero((unsigned int*)n, f_s, i);
}

void	if_else_x(void *n, t_format *f_s,
		int *hex_len, int *i)
{
	*i += ft_printf_char(f_s->wdth - ((f_s->acc < *hex_len)
			? (*hex_len) : f_s->acc), ' ');
	check_pr(i, f_s, n);
	*i += ft_printf_char(f_s->acc - (*hex_len), '0');
	if (f_s->mdf == 'l')
		ft_print_check_lxzero(n, f_s, i);
	else
		ft_print_check_xzero((unsigned int*)n, f_s, i);
}
