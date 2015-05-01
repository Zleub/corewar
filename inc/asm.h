/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 23:47:01 by adebray           #+#    #+#             */
/*   Updated: 2015/05/01 19:02:40 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include <libft.h>
# include <ft_printf.h>

typedef unsigned int	uint;

typedef struct			s_command
{
	t_op				*op;
	char				**raw_args;
	int					coding_octet;
	uint				size;
	uint				offset;
	struct s_command	*next;
}						t_command;

typedef struct			s_label
{
	char				*name;
	t_command			*target;
	struct s_label		*next;
}						t_label;

typedef struct			s_champion
{
	char				*name;
	char				*comment;
	t_command			*commands;
	t_label				*labels;
}						t_champion;

void		init(int argc, char const **argv);
int			open_file(char const *pathname);
t_champion	*get_champion(int new);
char		*get_current_line(char *line);

void		parse_file(int fd);
int			parse_comment(char const *line, uint row);
char const	*parse_label(char const *line, uint row);
int			parse_name(char const *line, uint row);
int			parse_command(char const *line, uint row);
void		usage(void);

t_label		*add_label(char *name);
t_label		*get_last_label(void);

t_command	*add_command(t_command *new);

void		die(char const *message);
void		die2(char *message, uint line, uint col);
char		*skip_white_spaces(char const *line);
int			is_number(char const *str);

char		**split_command(char const *s, uint *word);

#endif
