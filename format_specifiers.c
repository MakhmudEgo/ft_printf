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
	f_s->flag = 1;
	f_s->flag_second = 1;
	f_s->width = 0x0;
	f_s->accuracy = 0x0;
	f_s->modifier = 0x0;
	f_s->modifier_second = 0x0;
	f_s->modifier_x = 0x0;
	f_s->conversion_type = 0x0;
}

/*
** ' ' && '-'
** '+' && '-'
** '0' && ' '
** '0' && '+'
** '+' !gnored ' '
** '-' !gnored '0'
** %[флаги][ширина][точность][модификаторы][тип преобразования]
** %[flags][width][accuracy][modifiers][conversion type]
*/

static void	g_f_s_assist_1(const char *format, t_format *f_s)
{
	while (*format && (*format == ' ' || *format == '-'
	|| *format == '+' || *format == '0' || *format == '#'))
	{
		if (f_s->flag == 1 || (*format == '+' && f_s->flag == ' ')
			|| (*format == '-' && f_s->flag == '0'))
			f_s->flag = *format;
		else if ((f_s->flag_second == 1 && f_s->flag != *format) ||
		((*format == '+' && f_s->flag_second == ' ')
		|| (*format == '-' && f_s->flag_second == '0')))
			f_s->flag_second = *format;
		if (!f_s->modifier_x && *format == '#')
			f_s->modifier_x = *format;
		format++;
	}
}

static void	g_f_s_assist_2(const char *format, t_format *f_s, va_list ap)
{
	while (*format && *format >= '0' && *format <= '9')
	{
		f_s->width = (f_s->width * 10) + (*format - '0');
		format++;
	}
	if (*format == '.')
		format++;
	if (*format == '*')
	{
		f_s->accuracy = va_arg(ap, int);
		format++;
		while (*format && *format >= '0' && *format <= '9')
			format++;
	}
	while (*format && *format >= '0' && *format <= '9')
	{
		f_s->accuracy = (f_s->accuracy * 10) + (*format - '0');
		format++;
	}
}

static void	g_f_s_assist_3(const char *format, t_format *f_s)
{
	while (*format && (*format == 'h' || *format == 'l'
	|| *format == 'l' || *format == 'L'))
	{
		if (!f_s->modifier)
			f_s->modifier = *format;
		else if (!f_s->modifier_second && f_s->modifier == *format)
			f_s->modifier_second = *format;
		format++;
	}
	f_s->conversion_type = *format;
}

void		get_format_specifiers(const char *format, t_format *f_s, va_list ap)
{
	init_format_specifiers(f_s);
	g_f_s_assist_1(format, f_s);
	while (*format && (*format == ' ' || *format == '-'
	|| *format == '+' || *format == '0' || *format == '#'))
		format++;
	if (*format == '*')
	{
		f_s->width = va_arg(ap, int);
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
