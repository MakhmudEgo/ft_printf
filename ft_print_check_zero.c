/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_zero.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 16:26:02 by mizola            #+#    #+#             */
/*   Updated: 2020/06/26 12:14:54 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_print_check_zero(long long int *n, t_format *f_s, int *i)
{
	if ((f_s->acc == 0 && *n == 0))
		*i += f_s->wdth > 0 ? write(1, " ", 1) : 0;
	else
		ft_printf_signed(((*n < 0) ? -(*n) : *n), i);
}

void	ft_print_check_uzero(unsigned long long *n, t_format *f_s, int *i)
{
	if ((f_s->acc == 0 && *n == 0))
		*i += f_s->wdth > 0 ? write(1, " ", 1) : 0;
	else
		ft_printf_unsigned(*n, i);
}

void	ft_print_check_xzero(unsigned int *n, t_format *f_s, int *i)
{
	*i += f_s->flg_x && f_s->cnv_tp == 'x' ? write(1, "0x", 2) : 0;
	*i += f_s->flg_x && f_s->cnv_tp == 'X' ? write(1, "0X", 2) : 0;
	if ((f_s->acc == 0 && *n == 0))
		*i += f_s->wdth > 0 ? write(1, " ", 1) : 0;
	else
		print_x(f_s->cnv_tp, *n, i);
}

void	ft_print_check_lxzero(unsigned long long *n, t_format *f_s, int *i)
{
	*i += f_s->flg_x && f_s->cnv_tp == 'x' ? write(1, "0x", 2) : 0;
	*i += f_s->flg_x && f_s->cnv_tp == 'X' ? write(1, "0X", 2) : 0;
	if ((f_s->acc == 0 && *n == 0))
		*i += f_s->wdth > 0 ? write(1, " ", 1) : 0;
	else
		print_lx(f_s->cnv_tp, *n, i);
}
