# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 05:47:38 by gprada-t          #+#    #+#              #
#    Updated: 2023/12/12 15:56:59 by gprada-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
COLOR	= \033[1;39m
GREEN	= \033[1;32m
BLUE	= \033[1;34m
#                             ----- PROGRAM -----                              #
NAME 	= 	libft.a
#                  -----------       FILES       -----------                   #
HEADER	= 	libft.h
SRCS	=	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
 			ft_strlen.c ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strlcpy.c \
			ft_strlcat.c ft_strncmp.c ft_tolower.c ft_toupper.c ft_bzero.c \
			ft_calloc.c ft_strdup.c ft_atoi.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_strmapi.c ft_striteri.c \
			ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			ft_lstadd_back_bonus.c ft_lstlast_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
			get_next_line.c get_next_line_utils.c \
			ft_print_pointer.c ft_print_str.c ft_put_numbers.c ft_printf.c \
			ft_putstr.c ft_absolute.c ft_atoi_base.c ft_isspace.c \

OBJ		=	$(subst .c,.o,$(SRCS))
DEP		=	$(subst .c,.d,$(SRCS))
# ----------------------           COMMANDS                ------------------- #
INCLUDE	=	-I
CFLAGS	= 	-Wall -Wextra -Werror
#                       ------------ RU2LES --------------                     #
%.o: %.c Makefile
	@printf "$(GREEN)	\rCompiling -->$(BLUE)$<<------$(COLOR)		\r"
	@$(CC) -MT $@ $(CFLAGS) -MMD -MP $(INCLUDE) $(HEADER) -c $< -o $@

all:
	@echo ""
	@$(MAKE) $(NAME)

$(NAME): $(OBJ)
	@ar curs $(NAME) $(OBJ)
	@printf "\n$(GREEN) $(basename $(NAME)) created successfully.$(COLOR)"

clean:
	@rm -rf $(OBJ) $(DEP)
	@printf "\n$(GREEN) $(basename $(NAME)) created successfully.$(COLOR)"

fclean:
	@make clean
	@rm -rf libft.a
	@printf "\n$(GREEN) $(basename $(NAME)) removed successfully.$(COLOR)"

re: fclean all
	@printf "\n$(GREEN) $(basename $(NAME)) remade successfully.$(COLOR)"

.PHONY: all clean fclean re

-include $(DEP)
