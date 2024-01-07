CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -lreadline -I includes
RM = rm -rf

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,src/%.o,$(SRCS))
NAME = minimalianteo
HEADER = includes/*.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) Makefile
	@make -C libft > /dev/null
	@echo "🔨 Building $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME) > /dev/null
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
