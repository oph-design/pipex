# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 12:41:45 by oheinzel          #+#    #+#              #
#    Updated: 2023/01/13 12:32:19 by oheinzel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Variables

NAME		= pipex
INCLUDE		= include
LIBFT		= libft
SRC_DIR		= src/
OBJ_DIR		= obj/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I
RM			= rm -f
GREEN		= \033[0;32m
BLUE		= \033[1;36m
CYAN		= \033[0;36m
WHITE		= \033[0m

#Sources

SRC_FILES	=	main utils
SRC_B_FILES	=	main_bonus utils_bonus

SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
SRC_B		=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_B_FILES)))
OBJ_B		=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_B_FILES)))

###

OBJF		=	.cache_exists

all:		$(NAME)

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

bonus:		fclean $(OBJ_B)
			@make -C $(LIBFT)
			@cp libft/libft.a .
			@$(CC) $(CFLAGS) $(INCLUDE) libft.a $(OBJ_B) -o $(NAME)
			@$(RM) libft.a
			@echo "$(GREEN)pipex bonus compiled!$(WHITE)"

.PHONY:		all clean fclean re cmd
