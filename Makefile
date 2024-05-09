# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 07:48:42 by kmb               #+#    #+#              #
#    Updated: 2024/05/08 02:59:54 by kmb              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


######################--------------OLD------------------######################

# NAME = minishell

# CFLAGS = -Wall -Wextra -Werror -MMD -g -fsanitize=address
# CC = cc
# RM = rm -rf


# INCL = -I ./includes/
# READLINE = ./readline/
# READLINE_LIB = $(READLINE)libreadline.a
# RDLNHIST_LIB = $(READLINE)libhistory.a
# LINKEAD_LIB =  -lreadline
# MK_RL = make -C $(READLINE)

# MAIN = main
# BUILTINS = builtins builtins_2 new_environ enviroment history
# EXEC = exec finder pipes
# PARSING = heredoc lexer parsing redirections
# UTILS = frees handler inits utils


# F_BUILTINS = $(addprefix src/builtins/, $(BUILTINS))
# F_EXEC = $(addprefix src/exec/, $(EXEC))
# F_PARSING = $(addprefix src/parsing/, $(PARSING))
# F_UTILS = $(addprefix src/utils/, $(UTILS))
# F_MAIN = $(addprefix src/, $(MAIN))


# SRCS = $(addsuffix .c, $(BUILTINS) $(EXEC) $(PARSING) $(UTILS) \
# 		$(MAIN))

# OBJS = $(addprefix obj/, $(notdir $(SRCS:.c=.o)))
# DEPS = $(subst .o,.d,$(OBJS))


# RL_CONFIG = cd $(READLINE) && ./configure


# all: dir conf_rline libs $(NAME)

# all: $(NAME)

# conf_rline:
# 	 $(RL_CONFIG);

# libs:
# 	@make -C libft > /dev/null
# 	@make -C readline > /dev/null

# vpath %.c src/builtins src/exec src/parsing src/utils src/

# dir:
# 	@mkdir -p obj

# $(NAME): $(OBJS) ./libft/libft.a ./readline/libreadline.a ./readline/libhistory.a
# 	@make -C libft > /dev/null
# 	@make -C readline > /dev/null
# 	@$(CC) $(CFLAGS) $^ $(LINKEAD_LIB) -o $(NAME)
# 	@echo "✅✅$(NAME) is ready!✅✅"

# obj/%.o: %.c
# 	$(CC) $(CFLAGS) $(INCL) -c -D READLINE_LIBRARY=1 $< -o $@

# -include $(DEPS)

# fclean: clean
# 	@$(RM) $(NAME)
# 	@make fclean -C libft > /dev/null
# 	@echo "✅ Done cleaning up executables!"

# clean:
# 	@$(RM) obj
# 	@make clean -C readline > /dev/null
# 	@make clean -C libft > /dev/null
# 	@echo "✅ Done cleaning up!"

# re: fclean all

# .PHONY: all clean fclean re bonus rebonus


######################--------------NEW------------------######################

NAME = minishell

CFLAGS = -Wall -Wextra -Werror -MMD -g -fsanitize=address
CC = cc
RM = rm -rf

INCL = -I ./includes/
READLINE = ./libs/readline/
READLINE_LIB = $(READLINE)libreadline.a
RDLNHIST_LIB = $(READLINE)libhistory.a
LINKEAD_LIB =  -L$(READLINE) -lreadline -lncurses -lhistory
LIBFT = libs/libft/libft.a

MAIN = main
BUILTINS = builtins env_builtins history
ENVIROMENT = search change
EXEC = exec find
LEXER = hdoc quotes redir
PARSING = parse pipe
UTILS = free utils init error

F_BUILTINS = $(addprefix src/builtins/, $(BUILTINS))
F_ENVIROMENT = $(addprefix src/enviroment/, $(ENVIROMENT))
F_EXEC = $(addprefix src/exec/, $(EXEC))
F_LEXER = $(addprefix src/lexer/, $(LEXER))
F_PARSING = $(addprefix src/parsing/, $(PARSING))
F_UTILS = $(addprefix src/utils/, $(UTILS))
F_MAIN = $(addprefix src/, $(MAIN))

SRCS = $(addsuffix .c, $(F_BUILTINS) $(F_ENVIROMENT) \
$(F_EXEC) $(F_LEXER) $(F_PARSING) $(F_UTILS) $(F_MAIN))

OBJS = $(addprefix obj/, $(notdir $(SRCS:.c=.o)))
DEPS = $(subst .o,.d,$(OBJS))

RL_CONFIG = cd $(READLINE) && ./configure

all: dir conf_rline $(LIBFT) $(NAME)

conf_rline:
	@echo "⚙️ Configuring readline..."
	@$(RL_CONFIG)  > /dev/null
	@echo "✔️ readline configured!"

dir:
	@echo "� Creating object directory..."
	@mkdir -p obj
	@echo "✔️ Directory created!"

vpath %.c src/builtins src/exec src/parsing src/utils \
src/ src/enviroment src/lexer

$(LIBFT):
	@echo "🔨 Compiling libft..."
	@make -C libs/libft > /dev/null
	@echo "✔️ libft compiled!"

$(NAME): $(OBJS) $(LIBFT)
	@echo "🔨 Compiling readline..."
	@make -C libs/readline > /dev/null
	@echo "✔️ readline compiled!"
	@echo "🔨 Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $^ $(LINKEAD_LIB) -o $(NAME)
	@echo "✔️ $(NAME) compiled!"

obj/%.o: %.c
	@echo "🔨 Creating $@"
	@$(CC) $(CFLAGS) $(INCL) -c -D READLINE_LIBRARY=1 $< -o $@

-include $(DEPS)

fclean: clean
	@echo "🔨 Cleaning executables..."
	@$(RM) $(NAME)
	@make fclean -C libs/libft > /dev/null
	@echo "✔️ Executables cleaned!"

clean:
	@echo "🔨 Cleaning up..."
	@$(RM) obj
	@make clean -C libs/readline > /dev/null
	@make clean -C libs/libft > /dev/null
	@echo "✔️ Cleaned up!"

re: fclean all

.PHONY: all clean fclean re bonus rebonus
