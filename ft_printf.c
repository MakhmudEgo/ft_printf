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

void testt(va_list ap)
{

//	va_start(ap, format);
	char *s = va_arg(ap, char*);
	printf("%s\n", s);


}
int		ft_printf(const char *restrict format, ...)
{
	va_list			ap;
	int	i;

	i = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'p' || *format == 'x' || *format == 'X')
					i += (*format == 'p') ?
						 ft_printf_addr(*format, va_arg(ap, unsigned long)) :
						 ft_printf_addr(*format, va_arg(ap, int));
/*			else if (*format == 'c' || *format == 's')
				return 1;
			else if (*format == 'd' || *format == 'i' || *format == 'u')
				return 2;*/
			else
			{
				va_list tmp;
				va_copy(tmp, ap);
				testt(tmp);
			}
		}
		format++;
	}
	return (i);
}

int		main(void)
{
	char *s = "hello";
	int i = 5;
	ft_printf("%s%s", s, s);
/*	ft_printf("%p", s);
	write(1, "\n", 1);
	ft_printf("%X", s);*/

//	printf("|% 0.12d|", 16);


	//	printf("|%.qqthl;'\,z#13d|\n", i);
	return (0);
}
//0x101128fa8
//000000000000000000000000000000000000000000000000000000013
//00000000000000000000000000000000000000000000000000
//000000000000000000000000000013        13
//10-A; 11-B; 12-C; 13-D; 14-E; 15-F;