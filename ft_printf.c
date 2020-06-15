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
	setlocale(LC_CTYPE, "");
	char *s = "world";
	char c = '!';
	double n = 5.55;
/*	unsigned long long du = 18446744073709551615;
	long d = -9223372036854775824;
	int my_printf = ft_printf("n:hello % -# 0*123.*13p%c\n", 13, 15, s, c);
	int sys_printf = printf("o:hello %p%c\n", s, c);
	ft_printf("n:%d", d);
	printf("\no:%d\n", d);*/
	wchar_t cc = L'€';
	wchar_t *hh = L"╔══╦══╗  ┌──┬──┐  ╭──┬──╮  ╭──┬──╮  ┏━━┳━━┓  ┎┒┏┑   ╷  ╻ ┏┯┓ ┌┰┐    ▊ ╱╲╱╲╳╳╳\n"
				   "║┌─╨─┐║  │╔═╧═╗│  │╒═╪═╕│  │╓─╁─╖│  ┃┌─╂─┐┃  ┗╃╄┙  ╶┼╴╺╋╸┠┼┨ ┝╋┥    ▋ ╲╱╲╱╳╳╳\n"
				   "║│╲ ╱│║  │║   ║│  ││ │ ││  │║ ┃ ║│  ┃│ ╿ │┃  ┍╅╆┓   ╵  ╹ ┗┷┛ └┸┘    ▌ ╱╲╱╲╳╳╳\n"
				   "╠╡ ╳ ╞╣  ├╢   ╟┤  ├┼─┼─┼┤  ├╫─╂─╫┤  ┣┿╾┼╼┿┫  ┕┛┖┚     ┌┄┄┐ ╎ ┏┅┅┓ ┋ ▍ ╲╱╲╱╳╳╳\n"
				   "║│╱ ╲│║  │║   ║│  ││ │ ││  │║ ┃ ║│  ┃│ ╽ │┃  ░░▒▒▓▓██ ┊  ┆ ╎ ╏  ┇ ┋ ▎\n"
				   "║└─╥─┘║  │╚═╤═╝│  │╘═╪═╛│  │╙─╀─╜│  ┃└─╂─┘┃  ░░▒▒▓▓██ ┊  ┆ ╎ ╏  ┇ ┋ ▏\n"
				   "╚══╩══╝  └──┴──┘  ╰──┴──╯  ╰──┴──╯  ┗━━┻━━┛           └╌╌┘ ╎ ┗╍╍┛ ┋  ▁▂▃▄▅▆▇█\n";
	wchar_t *h1 = L"Braille:\n\n"
			   "⡌⠁⠧⠑ ⠼⠁⠒  ⡍⠜⠇⠑⠹⠰⠎ ⡣⠕⠌\n\n"
	  "⡍⠜⠇⠑⠹ ⠺⠁⠎ ⠙⠑⠁⠙⠒ ⠞⠕ ⠃⠑⠛⠔ ⠺⠊⠹⠲ ⡹⠻⠑ ⠊⠎ ⠝⠕ ⠙⠳⠃⠞\n"
   "⠱⠁⠞⠑⠧⠻ ⠁⠃⠳⠞ ⠹⠁⠞⠲ ⡹⠑ ⠗⠑⠛⠊⠌⠻ ⠕⠋ ⠙⠊⠎ ⠃⠥⠗⠊⠁⠇ ⠺⠁⠎\n"
   "⠎⠊⠛⠝⠫ ⠃⠹ ⠹⠑ ⠊⠇⠻⠛⠹⠍⠁⠝⠂ ⠹⠑ ⠊⠇⠻⠅⠂ ⠹⠑ ⠥⠝⠙⠻⠞⠁⠅⠻⠂\n"
   "⠁⠝⠙ ⠹⠑ ⠡⠊⠑⠋ ⠍⠳⠗⠝⠻⠲ ⡎⠊⠗⠕⠕⠛⠑ ⠎⠊⠛⠝⠫ ⠊⠞⠲ ⡁⠝⠙\n"
   "⡎⠊⠗⠕⠕⠛⠑⠰⠎ ⠝⠁⠍⠑ ⠺⠁⠎ ⠛⠕⠕⠙ ⠥⠏⠕⠝ ⠰⡡⠁⠝⠛⠑⠂ ⠋⠕⠗ ⠁⠝⠹⠹⠔⠛ ⠙⠑\n"
   "⠡⠕⠎⠑ ⠞⠕ ⠏⠥⠞ ⠙⠊⠎ ⠙⠁⠝⠙ ⠞⠕⠲\n\n"
   "⡕⠇⠙ ⡍⠜⠇⠑⠹ ⠺⠁⠎ ⠁⠎ ⠙⠑⠁⠙ ⠁⠎ ⠁ ⠙⠕⠕⠗⠤⠝⠁⠊⠇⠲\n\n"
   "⡍⠔⠙⠖ ⡊ ⠙⠕⠝⠰⠞ ⠍⠑⠁⠝ ⠞⠕ ⠎⠁⠹ ⠹⠁⠞ ⡊ ⠅⠝⠪⠂ ⠕⠋ ⠍⠹\n"
   "⠪⠝ ⠅⠝⠪⠇⠫⠛⠑⠂ ⠱⠁⠞ ⠹⠻⠑ ⠊⠎ ⠏⠜⠞⠊⠊⠥⠇⠜⠇⠹ ⠙⠑⠁⠙ ⠁⠃⠳⠞\n"
   "⠁ ⠙⠕⠕⠗⠤⠝⠁⠊⠇⠲ ⡊ ⠍⠊⠣⠞ ⠙⠁⠧⠑ ⠃⠑⠲ ⠔⠊⠇⠔⠫⠂ ⠍⠹⠎⠑⠇⠋⠂ ⠞⠕\n"
   "⠗⠑⠛⠜⠙ ⠁ ⠊⠕⠋⠋⠔⠤⠝⠁⠊⠇ ⠁⠎ ⠹⠑ ⠙⠑⠁⠙⠑⠌ ⠏⠊⠑⠊⠑ ⠕⠋ ⠊⠗⠕⠝⠍⠕⠝⠛⠻⠹\n"
   "⠔ ⠹⠑ ⠞⠗⠁⠙⠑⠲ ⡃⠥⠞ ⠹⠑ ⠺⠊⠎⠙⠕⠍ ⠕⠋ ⠳⠗ ⠁⠝⠊⠑⠌⠕⠗⠎\n"
   "⠊⠎ ⠔ ⠹⠑ ⠎⠊⠍⠊⠇⠑⠆ ⠁⠝⠙ ⠍⠹ ⠥⠝⠙⠁⠇⠇⠪⠫ ⠙⠁⠝⠙⠎\n"
   "⠩⠁⠇⠇ ⠝⠕⠞ ⠙⠊⠌⠥⠗⠃ ⠊⠞⠂ ⠕⠗ ⠹⠑ ⡊⠳⠝⠞⠗⠹⠰⠎ ⠙⠕⠝⠑ ⠋⠕⠗⠲ ⡹⠳\n"
   "⠺⠊⠇⠇ ⠹⠻⠑⠋⠕⠗⠑ ⠏⠻⠍⠊⠞ ⠍⠑ ⠞⠕ ⠗⠑⠏⠑⠁⠞⠂ ⠑⠍⠏⠙⠁⠞⠊⠊⠁⠇⠇⠹⠂ ⠹⠁⠞\n"
   "⡍⠜⠇⠑⠹ ⠺⠁⠎ ⠁⠎ ⠙⠑⠁⠙ ⠁⠎ ⠁ ⠙⠕⠕⠗⠤⠝⠁⠊⠇⠲\n";
	int myw = ft_printf("%S\n", hh);
	int oow = printf("%S\n", hh);


	int oct_1 = L'🤬'; //0b000010000001101001000;
	int oct_2 = L'🤬'; //0b000010000001101001000;
	int oct_3 = L'🤬'; //0b000010000001101001000;
	int oct_4 = L'🤬'; //0b000010000001101001000;

	int test_oct_1 = 0b11110000;
	int test_oct_2 = 0b10000000;
	int test_oct_3 = 0b10000000;
	int test_oct_4 = 0b10000000;

	oct_1 >>= 18;
	test_oct_1 |= oct_1;

	oct_2 &= 0b000111111000000000000;
	oct_2 >>= 12;
	test_oct_2 |= oct_2;

	oct_3 &= 0b000000000111111000000;
	oct_3 >>= 6;
	test_oct_3 |= oct_3;

	oct_4 &= 0b0000000000000000111111;
	test_oct_4 |= oct_4;

//	ft_printf("%c%c%c%c", test_oct_1,test_oct_2,test_oct_3,test_oct_4);

//	printf("Test%00 10d%++--''d%%ff%xsdf%%-6d\\n%-6d\\n%  -6d\\n", i, i, i, i, i);
//	printf("|%.qqthl;'\,z#13d|\n", i);
	return (0);
}
