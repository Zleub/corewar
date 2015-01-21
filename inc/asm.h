/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 23:47:01 by adebray           #+#    #+#             */
/*   Updated: 2015/01/19 23:51:41 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include <ft_libft.h>
# include <ft_printf.h>

typedef unsigned int	uint;

typedef struct			s_instruction
{
	int					opcode;
	struct instruction	*next;
}						t_instruction;

typedef struct			s_champion
{
	char				*name;
	char				*description;
}						t_champion;

void	init(int argc, char const **argv);
void	usage(void);
int		open_file(char const *pathname);

void	parse_file(int fd);
int		parse_comment(char const *line, uint row);
int		parse_label(char const *line, uint row);
int		parse_name(char const *line, uint row);

void	die(char const *message);
void	syntax_error(uint line, uint col);

#endif