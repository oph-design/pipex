# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oph <oph@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 12:41:45 by oheinzel          #+#    #+#              #
#    Updated: 2022/12/30 12:44:21 by oph              ###   ########.fr        #
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
MAGENTA		= \033[1;35m
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

cmd:		
			@echo "------------------------------$(MAGENTA)THE 42 COMMANDMENTS$(WHITE)--------------------------------"
			@echo "|	0: CC is the compiler, you shalt have no other compilers before them	|"
			@echo "|	1: You shalt not use any librarys name in vain				|"
			@echo "|	2: Remember the eval points, to keep them holy				|"
			@echo "|	3: Honour FdF and fract-ol						|"
			@echo "|	4: You shalt not register so_long					|"
			@echo "|	5: You shalt not cheat							|"
			@echo "|	6: You shalt not use ft_calloc, as it is the forbidden function		|"
			@echo "|	7: You shalt not bear paco --strict results against your evaluatee	|"
			@echo "|	8: You shalt not covet thy neighbours mouse				|"
			@echo "|	9: You shalt not covet thy neighbours leaderboard position		|"
			@echo "---------------------------------------------------------------------------------"

.PHONY:		all clean fclean re cmd