//
// Created by Makhmud Ego on 01.06.2020.
//

#ifndef PRINTF_LIBFTPRINTF_H
#define PRINTF_LIBFTPRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>

int		ft_printf(const char * restrict format, ...);
int		ft_printf_addr(int c, ...);

#endif
