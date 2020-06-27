/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_specifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 17:27:41 by mizola            #+#    #+#             */
/*   Updated: 2020/06/27 18:13:17 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	init_format_specifiers(t_format *f_s)
{
	f_s->is_mns = 0x0;
	f_s->is_zr = 0x0;
	f_s->is_pls = 0x0;
	f_s->is_spc = 0x0;
	f_s->flg_x = 0x0;
	f_s->wdth = 0x0;
	f_s->acc = -1;
	f_s->mdf = 0x0;
	f_s->mdf_ii = 0x0;
	f_s->cnv_tp = 0x0;
	f_s->amnt_prnt_c = 0x0;
}

/*
** ' ' && '-'
** '+' && '-'
** '0' && ' '
** '0' && '+'
** '+' !gnored ' '
** '-' !gnored '0'
** %[флаги][ширина][точность][модификаторы][тип преобразования]
** %[flgs][wdth][acc][mdfs][conversion type]
*/

static void	g_f_s_assist_1(const char *format, t_format *f_s)
{
	while (*format && (*format == ' ' || *format == '-'
	|| *format == '+' || *format == '0' || *format == '#' || *format == "'"[0]))
	{
		if (*format != "'"[0])
		{
			f_s->is_mns = *format == '-' ? 1 : f_s->is_mns;
			f_s->is_zr = *format == '0' ? 1 : f_s->is_zr;
			f_s->is_pls = *format == '+' ? 1 : f_s->is_pls;
			f_s->is_spc = *format == ' ' ? 1 : f_s->is_spc;
			f_s->flg_x = *format == '#' ? 1 : f_s->flg_x;
		}
		format++;
	}
}

static void	g_f_s_assist_2(const char *format, t_format *f_s, va_list ap)
{
	while (*format && *format >= '0' && *format <= '9')
	{
		f_s->wdth = (f_s->wdth * 10) + (*format - '0');
		format++;
	}
	if (*format == '.')
	{
		f_s->acc = 0;
		format++;
	}
	if (*format == '*')
	{
		f_s->acc = va_arg(ap, int);
		f_s->acc = f_s->acc < 0 ? -1 : f_s->acc;
		format++;
		while (*format && *format >= '0' && *format <= '9')
			format++;
	}
	while (*format && *format >= '0' && *format <= '9')
	{
		f_s->acc = (f_s->acc * 10) + (*format - '0');
		format++;
	}
}

static void	g_f_s_assist_3(const char *format, t_format *f_s)
{
	while (*format && (*format == 'h' || *format == 'l'
	|| *format == 'l' || *format == 'L'))
	{
		if (!f_s->mdf)
			f_s->mdf = *format;
		else if (!f_s->mdf_ii && f_s->mdf == *format)
			f_s->mdf_ii = *format;
		format++;
	}
	f_s->cnv_tp = *format;
}

void		get_format_specifiers(const char *format, t_format *f_s, va_list ap)
{
	init_format_specifiers(f_s);
	g_f_s_assist_1(format, f_s);
	while (*format && (*format == ' ' || *format == '-'
	|| *format == '+' || *format == '0' || *format == '#' || *format == "'"[0]))
		format++;
	if (*format == '*')
	{
		f_s->wdth = va_arg(ap, int);
		f_s->is_mns = f_s->wdth < 0 ? '-' : f_s->is_mns;
		f_s->wdth = f_s->wdth < 0 ? -f_s->wdth : f_s->wdth;
		format++;
		while (*format && *format >= '0' && *format <= '9')
			format++;
	}
	g_f_s_assist_2(format, f_s, ap);
	while (*format && ((*format >= '0' && *format <= '9')
	|| *format == '.' || *format == '*'))
		format++;
	g_f_s_assist_3(format, f_s);
}
