# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 10:50:05 by adebray           #+#    #+#              #
#    Updated: 2015/01/22 06:54:18 by amaurer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libasm.a
LIB			=	asm
HEADDIR		=	 ../../inc

SRC			=	op.c					init.c						parse.c    \
				get_next_line.c			parse_comment.c				util.c     \
				parse_label.c			parse_name.c				label.c

OBJ			= $(subst .c,.o,$(SRC))

CC			= gcc
CCFLAGS		= -Werror -Wall -Wextra -Wuninitialized -O3 -g

all: $(NAME)

$(NAME):	$(OBJ)
			@ar rc $@ $^
			@ranlib $@
			@echo '!'
			@echo "\033[32m•\033[0m asm compil: \033[32m$(NAME)\033[0m"

%.o:		%.c
			@echo '.''\c'
			@$(CC) $(CCFLAGS) -I $(HEADDIR) -o $@ -c $<

clean:
			@rm -f $(OBJ)
			@echo "\033[31m•\033[0m asm clean.\033[0m"

fclean:		clean
			@rm -f $(NAME)
			@echo "\033[31m•\033[0m asm fclean: \033[31m$(NAME)\033[0m"

re:			fclean all

.PHONY: all clean fclean re
