# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/11 14:02:02 by mizola            #+#    #+#              #
#    Updated: 2020/06/25 16:35:09 by mizola           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC = 	format_specifiers.c ft_numlen.c ft_numprint.c ft_printf_addr.c\
		ft_printf_char.c ft_printf_num.c ft_printf_sgnd.c ft_printf_unicode.c\
		ft_printf_usgnd.c ft_printf.c ft_strlen.c get_num_value.c ft_print_check_zero.c

OSRC = $(SRC:.c=.o)

HEADER = libftprintf.h

FLAGS = -Wall -Wextra -Werror -c -std=c99

all: $(NAME) $(OSRC)

$(NAME): $(SRC) $(HEADER)
	gcc $(FLAGS) $(SRC)
	ar rc $(NAME) $(OSRC)
	ranlib $(NAME)

bonus: $(OSRC)

$(OSRC): $(SRC)
	gcc $(FLAGS) $(SRC)
	ar rc $(NAME) $(OSRC)
	ranlib $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OSRC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
