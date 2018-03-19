# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akoller <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/27 23:33:54 by akoller           #+#    #+#              #
#    Updated: 2018/03/13 13:54:30 by akoller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

FLAGS	= -Wall -Wextra -Werror -I. -g -c

HEADER	= ftprintf.h

SRCS	= ft_printf.c \
			ft_escparse.c \
			ft_printvar.c \
			ft_isdigit.c \
			ft_atoi.c \
			ft_signed.c \
			ft_strlen.c \
			ft_unsigned.c \
			ft_stringput.c \
			ft_unsignedfunc.c \
			ft_strchr.c \
			ft_putstr.c \
			ft_charput.c

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
