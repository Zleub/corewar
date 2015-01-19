# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/10/02 03:26:29 by adebray           #+#    #+#              #
#    Updated: 2015/01/20 00:00:47 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	corewar
HEADDIR			=	inc
HEADFLAG		=	-I ./$(HEADDIR)

SRCDIR			=	src
SRC				=	$(SRCDIR)/main.c
OBJ				=	$(subst .c,.o,$(SRC))

CC				=	gcc
CCFLAGS			=	-Werror -Wall -Wextra -Wuninitialized -O3 -g3

LIBLIBFT		=	-L$(SRCDIR)/libft -lft
LIBPRINTF		=	-L$(SRCDIR)/ft_printf -lftprintf
LIBESSENTIAL	=	$(LIBLIBFT) $(LIBPRINTF)

LIBCOREWAR		=	-L$(SRCDIR)/corewar -lcorewar

LIBNCURSES		=	-L$(SRCDIR)/curse -lcurse
LIBGRAPHIC		=	-lncurses

LIBFLAG			=	$(LIBESSENTIAL) $(LIBCOREWAR) # $(LIBNCURSES) $(LIBGRAPHIC)

.PHONY: all clean fclean re $(NAME)

all:
	@echo "plz, specify corewar or asm"

makelib: _libft _printf _corewar # _curse

$(NAME): makelib $(OBJ)
	@$(CC) $(CCFLAGS) $(HEADFLAG) $(LIBFLAG) -o $(NAME) $(OBJ)
	@echo '!'
	@echo "\033[32m•\033[0m $(NAME) compil: \033[32m$(NAME)\033[0m"

_libft: $(HEADDIR)/libft.h
	@make -C $(SRCDIR)/libft

_printf: $(HEADDIR)/ft_printf.h
	@make -C $(SRCDIR)/ft_printf

_curse: $(HEADDIR)/curse.h
	@make -C $(SRCDIR)/curse

_corewar: $(HEADDIR)/corewar.h
	@make -C $(SRCDIR)/corewar

%.o: %.c
	@echo '.''\c'
	@$(CC) $(CCFLAGS) $(HEADFLAG) -o $@ -c $<

clean:
	@make -C $(SRCDIR)/libft clean
	@ #make -C $(SRCDIR)/curse clean
	@make -C $(SRCDIR)/ft_printf clean
	@make -C $(SRCDIR)/corewar clean
	@rm -f $(OBJ)
	@echo "\033[31m•\033[0m $(NAME) clean.\033[0m"

fclean: clean
	@make -C $(SRCDIR)/libft fclean
	@ #make -C $(SRCDIR)/curse fclean
	@make -C $(SRCDIR)/ft_printf fclean
	@make -C $(SRCDIR)/corewar fclean
	@rm -f $(OBJ)
	@rm -f $(LIBNAME)
	@rm -f $(NAME)
	@echo "\033[31m•\033[0m $(NAME) fclean: \033[31m$(NAME)\033[0m"

re: fclean all
