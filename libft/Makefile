# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akambou <akambou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 09:50:01 by akambou           #+#    #+#              #
#    Updated: 2023/11/23 00:26:46 by akambou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -o$(INCL)

INCL = includes/libft.h
OBJ_DIR = obj/
OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
SRCS = $(wildcard src/alloc/*.c src/chars/*.c src/lists/*.c \
src/memory/*.c src/numbers/*.c src/strings/*.c src/files/*.c \
src/printf/*.c)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@printf "\033[0;33m\rCompiling -> $< ✅                        \033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo -e "\033[0;32mLibft created 📚\033[0m"

clean:
	@$(RM) $(OBJ) $(OBJ_DIR)
	@echo -e "\033[0;31mCleaned objects 🧹\033[0m"

fclean: clean
	@$(RM) $(NAME) $(OBJ_DIR) $(OBJ)
	@echo -e "\033[0;31mCleaned libft 🧹\033[0m"
re: fclean all

.PHONY: all clean fclean re
