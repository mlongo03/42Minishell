# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/01 14:36:32 by fcarlucc          #+#    #+#              #
#    Updated: 2023/09/24 19:23:35 by lnicoter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = $(wildcard *.c)\

OBJ = $(SRC:.c=.o)

FLAGS =

LIBFT_PATH = ./libft

LIBFT = ${LIBFT_PATH}/libft.a

#COLORS
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

DEFAULT = \033[0m

all: $(NAME)

%.o : %.c
	@gcc -g $(FLAGS) -c $< -o  $@

$(NAME): $(OBJ)
	@make -C libft
	@make bonus -C libft
	@cc $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	@make clean -C libft
	@rm -f $(OBJ)
	@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "$(RED)all deleted!$(DEFAULT)"

re: clean fclean all

error:
	@sl
