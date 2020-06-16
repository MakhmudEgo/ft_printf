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

static int		ft_print_chars(va_list ap, t_format *f_s)
{
	int		i;
	char	c;
	char	*str;

	i = 0;
	str = 0x0;
	c = 0x0;
	if (f_s->modifier == 'l' || f_s->conversion_type == 'S')
		return (ft_printf_unicode(ap, f_s->conversion_type));
	if (f_s->conversion_type == 'c')
	{
		c = (char)va_arg(ap, int);
		i += write(1, &c, 1);
	}
	else
	{
		str = va_arg(ap, char*);
		if (!str)
			i += write(1, "(null)", 6);
		else
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
		i += ft_printf_addr(*format, ap, f_s);
	else if (*format == 's' || *format == 'c' || *format == 'S')
		i += ft_print_chars(ap, f_s);
	else if (*format == 'd' || *format == 'i' || *format == 'u')
		i += ft_printf_num(ap, f_s);
	else if (*format == '%')
		i += write(1, "%", 1);
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
/*
** %[флаги][ширина][точность][модификаторы][тип преобразования]
** %[flags][width][accuracy][modifiers][conversion type]
*/


int				main(void)
{
	int i = ft_printf("|%+- 08.5d|\n", 123456);
	int n = printf("|%+-- 8.5d|\n", 123456);

	ft_printf("Test%00 10d%++--'''12.9d%%ff%xsdf%%-6d\\n%-6d\\n%  -6d\\n\n", i, i, i, i, i);
	printf("Test%00 10d%++--'''12.9d%%ff%xsdf%%-6d\\n%-6d\\n%  -6d\\n\n", n, n, n, n, n);
//	printf("|%.qqthl;'\,z#13d|\n", i);
	return (0);
}
