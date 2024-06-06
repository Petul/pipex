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
CC := cc
CFLAGS := -Wall -Wextra -Werror
CFILES := pipex.c parse_commands.c pipes.c utils.c fd.c child.c main.c

LIBFT := libft/libft.a

OBJECTS := $(CFILES:.c=.o)

# BONUS_CFILES := ft_printf_bonus.c \
# 	ft_utoa_base_bonus.c \
# 	conversions_bonus.c \
# 	conversions2_bonus.c \
# 	parse_conversion_bonus.c \
# 	precision_bonus.c \
# 	printers_bonus.c \
# 	utils_bonus.c \
# 	plus_bonus.c \
# 	poundsign_bonus.c \
# 	field_width_bonus.c \
# 	space_bonus.c

# BONUS_OBJECTS := $(BONUS_CFILES:.c=.o)

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
	#rm -f .bonus
	make clean -C libft

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	make fclean -C libft

.PHONY: re
re: fclean all

	

	
	
# .PHONY: bonus
# bonus: .bonus

# .bonus: $(LIBFT) $(BONUS_OBJECTS)
# 	cp $(LIBFT) $(NAME)
# 	ar rcs $(NAME) $(BONUS_OBJECTS)
# 	touch .bonus
