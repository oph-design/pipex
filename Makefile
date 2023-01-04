# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 12:41:45 by oheinzel          #+#    #+#              #
#    Updated: 2023/01/04 14:32:54 by oheinzel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variables

NAME		= pipex
INCLUDE		= include
LIBFT		= libft
SRC_DIR		= src/
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -I #-Wall -Werror -Wextra#
RM			= rm -f
GREEN		= \033[0;32m
BLUE		= \033[1;36m
CYAN		= \033[0;36m
WHITE		= \033[0m

#Sources

SRC_FILES	=	main utils

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

###

OBJF		=	.cache_exists

all:		cmd $(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIBFT)
			@cp libft/libft.a .
			@$(CC) $(CFLAGS) $(INCLUDE) libft.a $(OBJ) -o $(NAME)
			@$(RM) libft.a
			@echo "$(GREEN)pipex compiled!$(WHITE)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(CYAN)Compiling $(WHITE): $<"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@make clean -C $(LIBFT)
			@echo "$(GREEN)pipex object files cleaned!$(WHITE)"

fclean:		clean
			@$(RM) -f $(NAME)
			@$(RM) -f $(LIBFT)/libft.a
			@echo "$(GREEN)pipex executable files cleaned!$(WHITE)"

re:			fclean all
			@echo "$(GREEN)Cleaned and rebuilt everything for pipex!$(WHITE)"

BLUE		= \033[1;36m
WHITE		= \033[0m

.PHONY:		all clean fclean re cmd
