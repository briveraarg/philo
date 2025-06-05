NAME	:=	philo

CC	:=	cc
CFLAGS	:=	-Wall -Wextra -Werror #-fsanitize=thread

SRC_DIR :=	src/
SRCS	:=	$(SRC_DIR)main.c

OBJ_DIR	:=	obj/
OBJS	:=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

INCLUDE	:=	include/philosophers.h

RED	:=	\033[91;1m
GREEN	:=	\033[92;1m
CLEAR_COLOR	:=	\033[0m
CYAN	:=	\033[96;1m

RM	:= rm -f

all:	$(NAME)

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

valgrind:
	valgrind -s \
		--leak-check=full \
		--show-leak-kinds=all \
		--show-reachable=yes \
		--track-origins=yes \
		./$(NAME)

norminette:
	@norminette $(SRCS) $(INCLUDE)

.PHONY: clean fclean re norminette valgrind

.DEFAULT_GOAL := all



