# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrouves <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/08 18:27:35 by mrouves           #+#    #+#              #
#    Updated: 2025/06/25 19:23:19 by mykle            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include sources/sources.mk

NAME 			:= scop

DIR_HEADERS		:= headers
DIR_SOURCES		:= sources
DIR_OBJS		:= .objs
DIR_LIB			:= lib

OBJS			:= $(addprefix $(DIR_OBJS)/, $(SOURCES:%.c=%.o))
OBJS_BONUS		:= $(addprefix $(DIR_OBJS)/, $(SOURCES_BONUS:%.c=%.o))

CC				:= clang
CFLAGS			:= -Wall -Wextra -Werror
LDFLAGS			:= -lm  -lglfw -ldl -lGL
IFLAGS			:= -I $(DIR_HEADERS)
DIR_DUP			= mkdir -p $(@D)

all: $(NAME) $(OBJS)

$(NAME): $(OBJS) $(ECS) $(MLX) $(LIBFT)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(IFLAGS) $^ -o $@
	@printf " $(CYAN)$(BOLD)$(ITALIC)■$(RESET)  compiled	$(BOLD)$@$(RESET) $(CYAN)successfully$(RESET)\n"

$(DIR_OBJS)/%.o: $(DIR_SOURCES)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf " $(BLUE)$(BOLD)$(ITALIC)■$(RESET)  compiling	$(GRAY)$(BOLD)$(ITALIC)$^$(RESET)\n"

clean:
	@rm -rf $(DIR_OBJS)
	@printf " $(GRAY)$(BOLD)$(ITALIC)■$(RESET)  cleaning	$(RED)$(BOLD)$(ITALIC)$(BUILD)$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf " $(GRAY)$(BOLD)$(ITALIC)■$(RESET)  deleted 	$(GRAY)$(BOLD)$(ITALIC)$(NAME)$(RESET)\n"

re: fclean all

.PHONY: clean fclean re all


BLACK		=	\033[30m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
MAGENTA		=	\033[35m
CYAN		=	\033[36m
WHITE		=	\033[37m
GRAY		=	\033[90m

BOLD		=	\033[1m
ITALIC		=	\033[3m

RESET		=	\033[0m
LINE_CLR	=	\33[2K\r

