# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/23 16:19:58 by brivera           #+#    #+#              #
#    Updated: 2025/06/26 19:56:57 by brivera          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	philo
CC	:=	cc
CFLAGS	:=	-Wall -Wextra -Werror #-g -fsanitize=thread
SRC_DIR :=	src/
SRCS	:=	$(SRC_DIR)main.c \
			$(SRC_DIR)utils.c \
			$(SRC_DIR)input_check.c \
			$(SRC_DIR)print_msj.c \
			$(SRC_DIR)init_struct.c \
			$(SRC_DIR)pthread_01.c \
			$(SRC_DIR)pthread_00.c \
			$(SRC_DIR)pthread_02.c \
			$(SRC_DIR)pthread_03.c \
			$(SRC_DIR)pthread_free.c \
			$(SRC_DIR)pthread_utils.c

OBJ_DIR	:=	obj/
OBJS	:= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

INCLUDE	:=	include/philosophers.h

RED		:=	\033[91;1m
GREEN		:=	\033[92;1m
CLEAR_COLOR	:=	\033[0m
CYAN		:=	\033[96;1m

RM	:= rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -Iinclude $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ Compilado PHILOSOPHERS\n$(CLEAR_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCLUDE)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)⛔ Limpieza de archivos objeto\n$(CLEAR_COLOR)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(RED)⛔ Limpieza total.\n$(CLEAR_COLOR)"

re:	fclean all
	@echo "$(CYAN)🔄 Proyecto reconstruido\n$(CLEAR_COLOR)"

# Memory leaks (Valgrind)
valgrind:
	valgrind \
		--tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=all \
		--show-reachable=yes \
		--track-origins=yes \
		./$(NAME) $(ARGS)
# make valgrind ARGS="1 800 200 200"

# Data races (Helgrind)
data_races:
	valgrind --tool=helgrind ./$(NAME)

norminette:
	@norminette $(SRCS) $(INCLUDE)

.PHONY: clean fclean re norminette valgrind data_races

.DEFAULT_GOAL := all