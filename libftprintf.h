/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 17:25:37 by mizola            #+#    #+#             */
/*   Updated: 2020/06/25 16:59:23 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_LIBFTPRINTF_H
# define PRINTF_LIBFTPRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <locale.h>

typedef struct		s_formatspecifiers
{
	char			flg;
	char			flg_ii;
	int				wdth;
	int				acc;
	char			mdf;
	char			mdf_ii;
	char			mdf_x;
	char			cnv_tp;
}					t_format;

int					ft_printf(const char *format, ...);
int					ft_printf_addr(char c, va_list ap, t_format *f_s);
void				get_format_specifiers(const char *format,
					t_format *f_s, va_list ap);
size_t				ft_strlen(const char *str);
int					ft_printf_num(va_list ap, t_format *f_s);
int					ft_printf_unicode(va_list ap, char c_arg);
int					ft_signed_numlen(long long int n);
int					ft_unsigned_numlen(unsigned long long int n);
void				ft_printf_unsigned(unsigned long long n, int *i);
void				ft_printf_signed(long long int n, int *i);
int					ft_printf_sgnd(va_list ap, t_format *f_s);
int					ft_printf_usgnd(va_list ap, t_format *f_s);
int					ft_printf_char(int n, char c);
long long int		get_sngd_value(va_list ap, t_format *f_s);
unsigned long long	get_usgnd_value(va_list ap, t_format *f_s);
void				ft_print_check_zero(long long int *n,
					t_format *f_s, int *i);
void				ft_print_check_uzero(unsigned long long *n,
					t_format *f_s, int *i);


#endif
