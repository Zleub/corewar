#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 11:21:22 by adebray           #+#    #+#              #
#    Updated: 2014/03/11 06:45:07 by gbir             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= libcorewar.a
LIB			= corewar
HEADDIR		= ../../inc

SRC			= op.c\
			corewar.c\
			heros.c\
			memory.c\
			process.c\
			instruction.c\
			ft.c\
			array.c

OBJ			= $(subst .c,.o,$(SRC))

CC			= gcc
CCFLAGS		= -Werror -Wall -Wextra -Wuninitialized -O3 -g

all: $(NAME)

$(NAME):	$(OBJ)
			@ar rc $@ $^
			@ranlib $@
			@echo '!'
			@echo "\033[32m•\033[0m compil: \033[32m$(NAME)\033[0m"

%.o:		%.c
			@echo '.''\c'
			@$(CC) $(CCFLAGS) -I $(HEADDIR) -o $@ -c $<

clean:
			@rm -f $(OBJ)
			@echo "\033[31m•\033[0m clean: \033[31m$(OBJ)\033[0m"

fclean:		clean
			@rm -f $(NAME)
			@echo "\033[31m•\033[0m fclean: \033[31m$(NAME)\033[0m"

re:			fclean all

.PHONY: all clean fclean re
