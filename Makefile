# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/10/02 03:26:29 by adebray           #+#    #+#              #
#    Updated: 2015/05/15 23:04:10 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	corewar
HEADDIR			=	inc
HEADFLAG		=	-I ./$(HEADDIR)

SRCDIR			=	src
SRC				=
OBJ				=	$(subst .c,.o,$(SRC))

CC				=	gcc
CCFLAGS			=	-Werror -Wall -Wextra -Wuninitialized -O3 -g

LIBLIBFT		=	-L$(SRCDIR)/libft -lft
LIBPRINTF		=	-L$(SRCDIR)/ft_printf -lftprintf
LIBESSENTIAL	=	$(LIBLIBFT) $(LIBPRINTF)

LIBNCURSES		=	-lncurses

LIBCOREWAR		=	$(LIBESSENTIAL) $(LIBNCURSES) -L$(SRCDIR)/corewar -lcorewar
LIBASM			=	$(LIBESSENTIAL) -L$(SRCDIR)/asm -lasm

.PHONY: all clean fclean re $(NAME) asm

all: $(NAME) asm

makelib: _libft _printf

$(NAME): makelib _vm $(OBJ)
	@$(CC) $(CCFLAGS) $(HEADFLAG) $(LIBCOREWAR) -o $(NAME) $(OBJ) $(SRCDIR)/main_vm.c
	@echo '!'
	@echo "\033[32m•\033[0m $(NAME) compil: \033[32m$(NAME)\033[0m"

asm: makelib _asm $(OBJ)
	@$(CC) $(CCFLAGS) $(HEADFLAG) $(LIBASM) -o $@ $(OBJ) $(SRCDIR)/main_asm.c
	@echo '!'
	@echo "\033[32m•\033[0m $@ compil: \033[32m$@\033[0m"

_libft: $(HEADDIR)/libft.h
	@make -C $(SRCDIR)/libft

_printf: $(HEADDIR)/ft_printf.h
	@make -C $(SRCDIR)/ft_printf

_curse: $(HEADDIR)/curse.h
	@make -C $(SRCDIR)/curse

_vm: $(HEADDIR)/corewar.h
	@make -C $(SRCDIR)/corewar

_asm: $(HEADDIR)/asm.h
	@make -C $(SRCDIR)/asm

%.o: %.c
	@echo '.''\c'
	@$(CC) $(CCFLAGS) $(HEADFLAG) -o $@ -c $<

clean:
	@make -C $(SRCDIR)/libft clean
	@ #make -C $(SRCDIR)/curse clean
	@make -C $(SRCDIR)/ft_printf clean
	@make -C $(SRCDIR)/corewar clean
	@make -C $(SRCDIR)/asm clean
	@rm -f $(OBJ)
	@echo "\033[31m•\033[0m $(NAME) clean.\033[0m"

fclean:
	@make -C $(SRCDIR)/libft fclean
	@ #make -C $(SRCDIR)/curse fclean
	@make -C $(SRCDIR)/ft_printf fclean
	@make -C $(SRCDIR)/corewar fclean
	@make -C $(SRCDIR)/asm fclean
	@rm -f $(OBJ)
	@rm -f $(LIBNAME)
	@rm -f $(NAME)
	@rm -f asm
	@echo "\033[31m•\033[0m $(NAME) fclean: \033[31m$(NAME)\033[0m"

re: fclean all
