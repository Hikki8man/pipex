NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

INC_PATH = include/
INC = pipex.h

LIB_PATH = libft/
LIB = libft.a

SRC_PATH = srcs
SRC = main.c

SRCS = $(addprefix $(SRC_PATH)/, $(SRC))

OBJS = $(SRCS:.c=.o)

%.o: %.c $(INC_PATH)$(INC)
	$(CC) $(CFLAGS) -I $(INC_PATH)$(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) libft_
	$(CC) $(CFLAGS) -o $@ -I $(INC_PATH)$(INC) $(OBJS) $(LIB_PATH)$(LIB)

libft_:
	make -C $(LIB_PATH)

clean:
	make -C $(LIB_PATH) clean
	$(RM) $(OBJS)

fclean:
	make -C $(LIB_PATH) fclean
	$(RM) $(OBJS)
	$(RM) $(NAME)

re: fclean all

.PHONY: all libft_ clean fclean re



