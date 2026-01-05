NAME	= push_swap
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I include
RM		= rm -f

SRC_DIR = ./src
OP_DIR  = $(SRC_DIR)/ops
PARSE_DIR = $(SRC_DIR)/parse
SORT_DIR = $(SRC_DIR)/sort
STACK_DIR = $(SRC_DIR)/stack
UTILS_DIR = $(SRC_DIR)/utils

SRCS = \
	$(SRC_DIR)/main.c \
	$(wildcard $(OP_DIR)/*.c) \
	$(wildcard $(PARSE_DIR)/*.c) \
	$(wildcard $(SORT_DIR)/*.c) \
	$(wildcard $(STACK_DIR)/*.c) \
	$(UTILS_DIR)/error.c

OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all