CC = gcc
CFLAGS = -Wall -Wextra -Werror -I includes #-fsanitize=address
RM = rm -rf

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,src/%.o,$(SRCS))
NAME = minimalianteo
HEADER = includes/*.h
READLINE = -lreadline -lhistory -L$(shell brew --prefix readline)/lib
	
all: $(NAME)

$(NAME): $(OBJS) $(HEADER) Makefile
	@make -C libft > /dev/null
	@echo "🔨 Building $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) $(READLINE) libft/libft.a -o $(NAME) > /dev/null
	@echo "✅ Done building $(NAME)!"

fclean: clean
	@echo "🧹 Cleaning up executables..."
	@$(RM) $(NAME) > /dev/null
	@make fclean -C libft > /dev/null
	@echo "✅ Done cleaning up executables!"

clean:
	@echo "🧹 Cleaning up..."
	@$(RM) $(OBJS) $(OBJSBONUS) > /dev/null
	@make clean -C libft  > /dev/null
	@echo "✅ Done cleaning up!"

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus
