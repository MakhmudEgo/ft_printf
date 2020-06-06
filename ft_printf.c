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

void			init_format_specifiers(t_format *f_s)
{
	f_s->flag = 1;
	f_s->flag_second = 1;
	f_s->width = 0x0;
	f_s->accuracy = 0x0;
	f_s->modifier = 0x0;
	f_s->modifier_second = 0x0;
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

void			get_format_specifiers(const char *format, t_format *f_s)
{
	init_format_specifiers(f_s);
	while (*format && (*format == ' ' || *format == '-'
	|| *format == '+' || *format == '0'))
	{
		if (f_s->flag == 1 || (*format == '+' && f_s->flag == ' ')
		|| (*format == '-' && f_s->flag == '0'))
			f_s->flag = *format;
		else if ((f_s->flag_second == 1 && f_s->flag != *format) ||
		((*format == '+' && f_s->flag_second == ' ')
		|| (*format == '-' && f_s->flag_second == '0')))
			f_s->flag_second = *format;
		format++;
	}
	while (*format && *format >= '0' && *format <= '9')
	{
		f_s->width = (f_s->width * 10) + (*format - '0');
		format++;
	}
	if (*format == '.')
		format++;
	while (*format && *format >= '0' && *format <= '9')
	{
		f_s->accuracy = (f_s->accuracy * 10) + (*format - '0');
		format++;
	}
	while (*format && (*format == 'h' || *format == 'l'
	|| *format == 'l' || *format == 'L'))
	{
		if (!f_s->modifier)
			f_s->modifier = *format;
		else if (f_s->modifier == *format && *format != 'L')
			f_s->modifier_second = *format;
		format++;
	}
	f_s->conversion_type = *format;
}

static int		ft_printf_assist(const char *format, va_list ap)
{
	int			i;
	t_format	f_s;

	i = 0;
	get_format_specifiers(format, &f_s);
	if (*format == 'p' || *format == 'x' || *format == 'X')
	{
		i = (*format == 'p') ?
			ft_printf_addr(*format, va_arg(ap, unsigned long)) :
			ft_printf_addr(*format, va_arg(ap, int));
	}
	return (i);
}

int				ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			i += ft_printf_assist(format, ap);
		}
		else
		{
			write(1, &(*format), 1);
			i++;
		}
		format++;
	}
	return (i);
}

int				main(void)
{
	char *s = "hello";
	char c = 'c';
	int i = -512;
	float n = 5;
//	ft_printf("%s", "world");
/*	ft_printf("%p", s);
	write(1, "\n", 1);
	ft_printf("%X", s);*/

//	ft_printf("%0 0 0 -+193.0000009531d", n);
//	printf("|% -0+d|", 1);
	long double dd = 2.2;
	printf("|%dd|\n", i);

	//	printf("|%.qqthl;'\,z#13d|\n", i);
	return (0);
}
//0x101128fa8
//000000000000000000000000000000000000000000000000000000013
//00000000000000000000000000000000000000000000000000
//000000000000000000000000000013        13
//10-A; 11-B; 12-C; 13-D; 14-E; 15-F;



/*
 * else if (*format == 'c' || *format == 's')
				return 1;
			else if (*format == 'd' || *format == 'i' || *format == 'u')
				return 2;*/
