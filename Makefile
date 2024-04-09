# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akambou <akambou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 07:48:42 by kmb               #+#    #+#              #
#    Updated: 2024/04/10 00:50:22 by akambou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# CC = gcc -std=c11
# CFLAGS = -fsanitize=address -I includes -MMD -MP
# LDFLAGS = -lreadline
# RM = rm -rf

# SRCS = $(wildcard src/builtins/*.c src/exec/*.c src/expansor/*.c src/main.c src/parsing/*.c src/utils/*.c)
# OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))
# DEPS = $(OBJS:.o=.d)
# NAME = minishell
# HEADER = includes/minishell.h
# DEP_FLAGS = -MMD -MP
# READLINE_SRCS = $(wildcard ../readline/*.c)
# READLINE_OBJS = $(READLINE_SRCS:.c=.o)

# all: $(NAME)

# $(NAME): $(OBJS) $(READLINE_OBJS)
# 	@make -C libft > /dev/null
# 	@$(CC) $(CFLAGS) $^ libft/libft.a -o $@ $(LDFLAGS) > /dev/null
# 	@echo "✅✅$(NAME) is ready!✅✅"

# obj/%.o: src/%.c
# 	@mkdir -p $(@D)
# 	@$(CC) $(CFLAGS) -c $< -o $@

# ../readline/%.o: ../readline/%.c
# 	@$(CC) $(CFLAGS) -c $< -o $@

# -include $(DEPS)

# fclean: clean
# 	@$(RM) $(NAME) > /dev/null
# 	@make fclean -C libft > /dev/null
# 	@echo "✅ Done cleaning up executables!"

# clean:
# 	@$(RM) obj > /dev/null
# 	@$(RM) $(READLINE_OBJS) > /dev/null
# 	@make clean -C libft  > /dev/null
# 	@echo "✅ Done cleaning up!"

# re: fclean all

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -MMD -g -fsanitize=address
CC = cc
RM = rm -rf


INCL = -I ./includes/
READLINE = ./readline/
READLINE_LIB = $(READLINE)libreadline.a
RDLNHIST_LIB = $(READLINE)libhistory.a
LINKEAD_LIB = -ltermcap -lreadline
MK_RL = make -C $(READLINE)

MAIN = main
BUILTINS = builtins enviroment expansor history
EXEC = exec finder pipes
PARSING = lexer parsing redirections
UTILS = frees handler inits


F_BUILTINS = $(addprefix src/builtins/, $(BUILTINS))
F_EXEC = $(addprefix src/exec/, $(EXEC))
F_PARSING = $(addprefix src/parsing/, $(PARSING))
F_UTILS = $(addprefix src/utils/, $(UTILS))
F_MAIN = $(addprefix src/, $(MAIN))


SRCS = $(addsuffix .c, $(BUILTINS) $(EXEC) $(PARSING) $(UTILS) \
		$(MAIN))

OBJS = $(addprefix obj/, $(notdir $(SRCS:.c=.o)))
DEPS = $(subst .o,.d,$(OBJS))


RL_CONFIG = cd $(READLINE) && ./configure


all: dir conf_rline libs $(NAME)

all: $(NAME)

conf_rline:
	 $(RL_CONFIG);

libs:
	@make -C libft > /dev/null
	@make -C readline > /dev/null

vpath %.c src/builtins src/exec src/parsing src/utils src/

dir:
	@mkdir -p obj

$(NAME): $(OBJS) ./libft/libft.a ./readline/libreadline.a ./readline/libhistory.a
	@make -C libft > /dev/null
	@make -C readline > /dev/null
	@$(CC) $(CFLAGS) $^ $(LINKEAD_LIB) -o $(NAME)
	@echo "✅✅$(NAME) is ready!✅✅"

obj/%.o: %.c
	$(CC) $(CFLAGS) $(INCL) -c -D READLINE_LIBRARY=1 $< -o $@

-include $(DEPS)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft > /dev/null
	@echo "✅ Done cleaning up executables!"

clean:
	@$(RM) obj
	@make clean -C readline > /dev/null
	@make clean -C libft > /dev/null
	@echo "✅ Done cleaning up!"

re: fclean all

.PHONY: all clean fclean re bonus rebonus