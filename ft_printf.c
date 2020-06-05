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
//' ' && '-'
//'+' && '-'
//'0' && ' '
//'0' && '+'
//'+' !gnored ' '
//'-' !gnored '0'
void		get_format_specifiers(const char *format, t_format *f_s)
{
	init_format_specifiers(f_s);
	while (*format != '\0' && !f_s->conversion_type)
	{
		while (*format && (*format == ' ' || *format == '-' ||
		*format == '+' || *format == '0'))
		{
			if (f_s->flag == 1)
				f_s->flag = *format;
			else if (f_s->flag_second == 1 && f_s->flag_second != f_s->flag)
				f_s->flag_second = *format;
//			if ()
			format++;
		}
		format++;
//		else if ();
	}
}

static int		ft_printf_assist(const char *format, va_list ap)
{
	int i;
	t_format f_s;

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
	int i = 511;
	float n = 5;
//	ft_printf("%s", "world");
	ft_printf("% -0+d", n);
/*	ft_printf("%p", s);
	write(1, "\n", 1);
	ft_printf("%X", s);*/

	printf("|% -0+d|", 1);


	//	printf("|%.qqthl;'\,z#13d|\n", i);
	return (0);
}
//0x101128fa8
//000000000000000000000000000000000000000000000000000000013
//00000000000000000000000000000000000000000000000000
//000000000000000000000000000013        13
//10-A; 11-B; 12-C; 13-D; 14-E; 15-F;



/*
 *
 * else if (*format == 'c' || *format == 's')
				return 1;
			else if (*format == 'd' || *format == 'i' || *format == 'u')
				return 2;*/