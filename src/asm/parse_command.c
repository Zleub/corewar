/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 07:08:17 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/23 05:47:19 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	op_tab[2] = {
	{"sti", 3, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

static t_op	*get_command(char const *command)
{
	uint	i;

	i = 0;

	while (op_tab[i].name)
	{
		ft_printf("|%s| |%s|\n", op_tab[i].name, command);
		if (ft_strequ(op_tab[i].name, command))
			return (&(op_tab[i]));
		i++;
	}

	return (NULL);
}

static char	*get_command_name(char const *line)
{
	char const	*save;

	save = line;

	while (ft_strchr(LABEL_CHARS, *line))
		line++;

	return ft_strndup((char *)save, line - save);
}


int		parse_command(char const *line, uint row)
{
	char		*name;
	char		**args;
	uint		argc;
	t_op		*op;

	name = get_command_name(line);
	op = get_command(name);

	if (op == NULL)
		die2("Unknown command", row, skip_white_spaces(line) - line);

	args = ft_strsplit(line + ft_strlen(name), SEPARATOR_CHAR);

	argc = 0;

	while (args[argc])
		argc++;

	if (op->arg_number != argc)
		die2("Bad argument count", row, skip_white_spaces(line) - line);

	return (0);
}