/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 20:43:18 by mizola            #+#    #+#             */
/*   Updated: 2020/05/31 16:57:22 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		ft_print_chars(va_list ap, const char c_arg)
{
	int		i;
	char	c;
	char	*str;

	i = 0;
	str = 0x0;
	c = 0x0;
	if (c_arg == 'c')
	{
		c = (char)va_arg(ap, int);
		i += write(1, &c, 1);
	}
	else
	{
		str = va_arg(ap, char*);
		i += write(1, str, ft_strlen(str));
	}
	return (i);
}

static int		ft_printf_assist(const char *format, va_list ap, t_format *f_s)
{
	int			i;

	i = 0;
	while (*format && *format != f_s->conversion_type)
		format++;
	if (*format == 'p' || *format == 'x' || *format == 'X')
		i += ft_printf_addr(*format, ap, f_s->modifier_x);
	else if (*format == 's' || *format == 'c')
		i += ft_print_chars(ap, *format);
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
			while (*format && *format != f_s.conversion_type)
				format++;
		}
		else
			i += write(1, &(*format), 1);
		format++;
	}
	return (i);
}

int				main(void)
{
	char *s = "world";
	char c = '!';
	double n = 5.55;
	int d = n * 1000;
	int my_printf = ft_printf("hello % -# 0*123.*13p%c\n", 13, 15, s, c);
	int sys_printf = printf("hello %p%c\n", s, c);


//	printf("Test%00 10d%++--''d%%ff%xsdf%%-6d\\n%-6d\\n%  -6d\\n", i, i, i, i, i);
//	printf("|%.qqthl;'\,z#13d|\n", i);
	return (0);
}
