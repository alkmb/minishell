# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 07:48:42 by kmb               #+#    #+#              #
#    Updated: 2024/03/02 21:59:06 by kmb              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -fsanitize=address -I includes -lreadline -MMD -MP
RM = rm -rf

SRCS = $(wildcard src/builtins/*.c src/exec/*.c src/expansor/*.c src/main.c src/parsing/*.c src/utils/*.c)
OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))
DEPS = $(OBJS:.o=.d)
NAME = minishell
HEADER = includes/minishell.h
DEP_FLAGS = -MMD -MP

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft > /dev/null
	@$(CC) $(CFLAGS) $^ libft/libft.a -o $@ > /dev/null
	@echo "✅✅$(NAME) is ready!✅✅"

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

fclean: clean
	@$(RM) $(NAME) > /dev/null
	@make fclean -C libft > /dev/null
	@echo "✅ Done cleaning up executables!"

clean:
	@$(RM) obj > /dev/null
	@make clean -C libft  > /dev/null
	@echo "✅ Done cleaning up!"

re: fclean all

.PHONY: all clean fclean re bonus rebonus
