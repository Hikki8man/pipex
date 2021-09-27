NAME = pipex
CC = gcc
CFLAGS = -Werror -Wextra -Wall
RM = rm -rf

INC_PATH = ../include/
INC = pipex.h

LIB_PATH = ../libft/
LIB = libft.a

SRC_PATH = ../srcs
SRC =	ft_init_data.c \
		ft_parsing.c \
		ft_command_list.c \
		ft_malloc_pipes.c \
		ft_create_process.c \
		ft_close_fd.c \
		ft_exit_error.c

SRCS = $(addprefix $(SRC_PATH)/, $(SRC)) \
		main_bonus.c

OBJS = $(SRCS:.c=.o)

%.o: %.c $(INC_PATH)$(INC)
	$(CC) $(CFLAGS) -I $(INC_PATH)$(INC) -c $< -o $@

all: libft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ -I $(INC_PATH)$(INC) $(OBJS) $(LIB_PATH)$(LIB)
	mv $@ ../

libft:
	make -C $(LIB_PATH)

clean:
	make -C $(LIB_PATH) clean
	$(RM) $(OBJS)

fclean:
	make -C $(LIB_PATH) fclean
	$(RM) $(OBJS)
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all libft clean fclean re
