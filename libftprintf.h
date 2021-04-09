/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 17:25:37 by mizola            #+#    #+#             */
/*   Updated: 2020/06/27 18:17:59 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <locale.h>

typedef struct s_formatspecifiers
{
	int				is_mns;
	int				is_zr;
	int				is_pls;
	int				is_spc;
	int				flg_x;
	int				wdth;
	int				acc;
	char			mdf;
	char			mdf_ii;
	char			cnv_tp;
	size_t			amnt_prnt_c;
}					t_format;

int					ft_printf(const char *format, ...);
int					ft_printf_addr(va_list ap, t_format *f_s);
void				get_format_specifiers(const char *format,
						t_format *f_s, va_list ap);
int					ft_strlen(const char *str);
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
int					ft_printf_x(va_list ap, t_format *f_s);
void				print_x(char c, unsigned int n, int *i);
void				print_lx(char c, unsigned long long n, int *i);
void				ft_print_check_xzero(unsigned int *n,
						t_format *f_s, int *i);
void				ft_print_check_lxzero(unsigned long long *n,
						t_format *f_s, int *i);
void				if_minus_x(void *n, t_format *f_s,
						int *hex_len, int *i);
void				if_plus_x(void *n, t_format *f_s,
						int *hex_len, int *i);
void				if_space_x(void *n, t_format *f_s,
						int *hex_len, int *i);
void				if_else_x(void *n, t_format *f_s,
						int *hex_len, int *i);
void				if_zero_x(void *n, t_format *f_s,
						int *hex_len, int *i);
void				check_pr(int *i, t_format *f_s, void *n);
void				ft_printf_n(int i, va_list ap);

#endif
