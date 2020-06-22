/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_specifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 17:27:41 by mizola            #+#    #+#             */
/*   Updated: 2020/06/07 17:27:42 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	init_format_specifiers(t_format *f_s)
{
	f_s->flg = 1;
	f_s->flg_ii = 1;
	f_s->wdth = 0x0;
	f_s->acc = -1;
	f_s->mdf = 0x0;
	f_s->mdf_ii = 0x0;
	f_s->mdf_x = 0x0;
	f_s->cnv_tp = 0x0;
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
			if (f_s->flg == 1 || (*format == '+' && f_s->flg == ' ')
				|| (*format == '-' && f_s->flg == '0'))
				f_s->flg = *format;
			else if ((f_s->flg_ii == 1 && f_s->flg != *format) ||
			((*format == '+' && f_s->flg_ii == ' ')
			|| (*format == '-' && f_s->flg_ii == '0')
			   || (f_s->flg == '+' && f_s->flg_ii == ' ')))
				f_s->flg_ii = *format;
			if (!f_s->mdf_x && *format == '#')
				f_s->mdf_x = *format;
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
