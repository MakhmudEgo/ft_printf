/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_usgnd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 16:00:57 by mizola            #+#    #+#             */
/*   Updated: 2020/06/22 16:01:03 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	if_minus(unsigned long long *n, t_format *f_s,
                        int *num_len, int *i)
{
    *i += (*n < 0) ? write(1, "-", 1) : 0;
    *i += ft_printf_char(f_s->acc - *num_len, '0');
    ft_printf_unsigned(*n, i);
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
    ft_printf_unsigned(*n, i);
}

static void	if_space(unsigned long long *n, t_format *f_s,
                        int *num_len, int *i)
{
    if (*n < 0)
    {
        *i += f_s->acc != -1 && f_s->acc < *num_len ?
              ft_printf_char(f_s->wdth - *num_len - 1, ' ') : 0;
        *i += f_s->acc != -1 && f_s->acc > *num_len ?
              ft_printf_char(f_s->wdth - f_s->acc - 1, ' ') : 0;
        *i += write(1, "-", 1);
    }
    else if (f_s->acc < *num_len)
        *i += write(1, " ", 1);
    *i += f_s->acc == -1 && (f_s->flg == '0' || f_s->flg_ii == '0') ?
          ft_printf_char(f_s->wdth - *num_len - 1, '0') : 0;
    if (*n >= 0)
    {
        *i += f_s->acc != -1 && f_s->acc > *num_len ?
              ft_printf_char(f_s->wdth - f_s->acc - 1, ' ') : 0;
        *i += f_s->acc != -1 && f_s->acc < *num_len ?
              ft_printf_char(f_s->wdth - *num_len - 1, ' ') : 0;
    }
    *i += f_s->acc == -1 && (f_s->flg != '0' && f_s->flg_ii != '0') ?
          ft_printf_char(f_s->wdth - *num_len - 1, ' ') : 0;
    *i += f_s->acc != -1 ? ft_printf_char(f_s->acc - *num_len, '0') : 0;
    ft_printf_unsigned(*n, i);
}

static void	if_else(unsigned long long *n, t_format *f_s,
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
    ft_printf_unsigned(*n, i);
}

int		ft_printf_usgnd(va_list ap, t_format *f_s)
{
    int				    num_len;
    unsigned long long  n;
    int				    i;

    i = 0;
    n = get_usgnd_value(ap, f_s);
    num_len = ft_unsigned_numlen(n);
    if (f_s->flg == '-' || f_s->flg_ii == '-')
        if_minus(&n, f_s, &num_len, &i);
    else if (f_s->flg == '+' || f_s->flg_ii == '+')
        if_plus(&n, f_s, &num_len, &i);
    else if ((f_s->flg == ' ' || f_s->flg_ii == ' '))
    {
        num_len += (n < 0) ? -1 : 0;
        if_space(&n, f_s, &num_len, &i);
    }
    else
        if_else(&n, f_s, &num_len, &i);
    return (i);
}