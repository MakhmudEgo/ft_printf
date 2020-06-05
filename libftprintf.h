/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 17:25:37 by mizola            #+#    #+#             */
/*   Updated: 2020/06/05 17:25:42 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_LIBFTPRINTF_H
# define PRINTF_LIBFTPRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>

typedef struct	s_formatspecifiers
{
	char		flag;
	char		flag_second;
	int			width;
	int			accuracy;
	char		modifier;
	char		modifier_second;
	char		conversion_type;
}				t_format;

int				ft_printf(const char *format, ...);
int				ft_printf_addr(int c, ...);

#endif
