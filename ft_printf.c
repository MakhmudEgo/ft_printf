/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 20:43:18 by mizola            #+#    #+#             */
/*   Updated: 2020/06/27 12:12:46 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		ft_print_chars_c(t_format *f_s, char c)
{
	int i;

	i = 0;
	i += f_s->is_mns ? write(1, &c, 1) : 0;
	i += ft_printf_char(f_s->wdth - 1, ' ');
	i += !f_s->is_mns ? write(1, &c, 1) : 0;
	return (i);
}

static int		ft_print_chars_s(t_format *f_s, char *s)
{
	int	i;
	int	s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (f_s->acc != -1)
		s_len = f_s->acc > (int)ft_strlen(s) ? ft_strlen(s) : f_s->acc;
	i += f_s->is_mns ? write(1, s, s_len) : 0;
	i += ft_printf_char(f_s->wdth - s_len, ' ');
	i += !f_s->is_mns ? write(1, s, s_len) : 0;
	return (i);
}

static int		ft_print_chars(va_list ap, t_format *f_s)
{
	int		i;
	char	*str;

	i = 0;
	str = 0x0;
	if (f_s->mdf == 'l' || f_s->cnv_tp == 'S')
		return (ft_printf_unicode(ap, f_s->cnv_tp));
	if (f_s->cnv_tp == 'c')
		i += ft_print_chars_c(f_s, (char)va_arg(ap, int));
	else
	{
		str = va_arg(ap, char*);
		if (!str)
			i += ft_print_chars_s(f_s, "(null)");
		else
			i += ft_print_chars_s(f_s, str);
	}
	return (i);
}

static int		ft_printf_assist(const char *format, va_list ap, t_format *f_s)
{
	int			i;

	i = 0;
	while (*format && *format != f_s->cnv_tp)
		format++;
	if (*format == 'p')
		i += ft_printf_addr(ap, f_s);
	else if (*format == 'x' || *format == 'X')
		i += ft_printf_x(ap, f_s);
	else if (*format == 's' || *format == 'c' || *format == 'S')
		i += ft_print_chars(ap, f_s);
	else if (*format == 'd' || *format == 'i' || *format == 'u')
		i += ft_printf_num(ap, f_s);
	else if (*format == '%')
	{
		i += f_s->is_mns ? write(1, "%", 1) : 0;
		i += f_s->is_zr && !f_s->is_mns ?
				ft_printf_char(f_s->wdth - 1, '0') : 0;
		i += !f_s->is_zr || f_s->is_mns ? ft_printf_char(f_s->wdth - 1, ' ') : 0;
		i += !f_s->is_mns ? write(1, "%", 1) : 0;
	}
	return (i);
}

/*
** c+s+p+diu+x+X+%
** [-0.*]+
** n f g e
** l ll h hh
** l ll h hh
** [# space +]+
*/

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	int			i;
	t_format	f_s;

	i = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			get_format_specifiers(format, &f_s, ap);
			i += ft_printf_assist(format, ap, &f_s);
			while (*format && *format != f_s.cnv_tp)
				format++;
		}
		else
			i += write(1, &(*format), 1);
		format++;
	}
	va_end(ap);
	return (i);
}
/*
** %[флаги][ширина][точность][модификаторы][тип преобразования]
** %[flags][width][accuracy][mdfs][conversion type]
*/
