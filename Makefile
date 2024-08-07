# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 14:22:58 by pleander          #+#    #+#              #
#    Updated: 2024/06/06 15:51:11 by pleander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
CC := gcc
CFLAGS := -Wall -Wextra -Werror
CFILES := pipex.c \
	argv_split.c \
	argv_split_utils.c \
	parse_commands.c \
	pipes.c \
	utils.c \
	fd.c \
	child.c \
	here_doc.c \
	main.c

BONUS_CFILES := pipex_bonus.c \
	argv_split_bonus.c \
	argv_split_utils_bonus.c \
	parse_commands_bonus.c \
	pipes_bonus.c \
	utils_bonus.c \
	fd_bonus.c \
	child_bonus.c \
	here_doc_bonus.c \
	main_bonus.c

LIBFT := libft/libft.a

OBJECTS := $(CFILES:.c=.o)

CFILES := $(addprefix mandatory/, $(CFILES))
OBJECTS := $(CFILES:.c=.o)

BONUS_CFILES := $(addprefix bonus/, $(BONUS_CFILES))
BONUS_OBJECTS := $(BONUS_CFILES:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f $(BONUS_OBJECTS)
	rm -f .bonus
	make clean -C libft

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	make fclean -C libft

.PHONY: re
re: fclean all

.PHONY: bonus
bonus: .bonus

.bonus: $(LIBFT) $(BONUS_OBJECTS)
	$(CC) $(BONUS_OBJECTS) $(LIBFT) -o $(NAME)
	touch .bonus
