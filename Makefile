# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoller <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/27 23:33:54 by akoller           #+#    #+#              #
#    Updated: 2018/02/27 23:33:57 by akoller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

FLAGS	= -Wall -Wextra -Werror -I. -c -g

HEADER	= ftprintf.h

SRCS	= ft_printf.c \
			ft_escparse.c \
			ft_printvar.c \
			ft_isdigit.c \
			ft_atoi.c \
			ft_signed.c \
			ft_strlen.c \
			ft_unsigned.c

OBJS	= $(SRCS:.c=.o)

$(NAME): 
	gcc $(FLAGS) $(SRCS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

clean:
	rm -f rm $(OBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: fclean clean re
