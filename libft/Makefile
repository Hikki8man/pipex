# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 14:15:55 by jchevet           #+#    #+#              #
#    Updated: 2020/11/30 11:36:35 by jchevet          ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRC =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memchr.c ft_memcmp.c\
		ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c 		\
		ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c \
		ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_tolower.c ft_toupper.c ft_strtrim.c ft_substr.c\
        ft_lstnew.c ft_lstadd_front.c ft_lstlast.c ft_lstsize.c ft_lstadd_back.c\
        ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_putstr.c\
        ft_putchar.c ft_putnbr.c ft_u_itoa.c ft_u_itoa_base.c ft_itoa_base.c ft_ullitoa_base.c get_next_line.c\
        ft_free_tab.c ft_printf/ft_flags.c ft_printf/ft_get_prec_width.c ft_printf/ft_print_c_str.c \
        ft_printf/ft_print_int.c ft_printf/ft_print_p_u_x.c \
        ft_printf/ft_print_percent.c ft_printf/ft_printf.c \
        ft_printf/ft_put_field_and_prec.c ft_putstr_nl_fd.c ft_free_str_tab.c

OBJ = ${SRC:.c=.o}

CC = gcc

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

NAME = libft.a

%.o: %.c include/libft.h include/ft_printf.h
		${CC} ${CFLAGS} -c $< -o $@

$(NAME): ${OBJ}
		ar -rc ${NAME} ${OBJ}
		ranlib ${NAME}

all: ${NAME}
		
clean:
		${RM} ${OBJ}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY:		all clean fclean re