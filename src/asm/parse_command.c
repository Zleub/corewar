/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 07:08:17 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/24 02:07:46 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

uint	lel[3] = {
	T_REG,
	T_REG | T_DIR | T_IND,
	T_DIR | T_REG
};

t_op	op_tab[2] = {
	{"sti", 3, lel, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};

static t_op	*get_op(char const *command)
{
	uint	i;

	i = 0;

	while (op_tab[i].name)
	{
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

static int	get_arg_type(char const *arg)
{
	if (!arg)
		return (0);

	if (arg[0] == 'r')
		return (T_REG);
	else if (arg[0] == DIRECT_CHAR)
		return T_DIR;
	else if (ft_isdigit(arg[0]) || arg[0] == LABEL_CHAR)
		return T_IND;

	return (0);
}

static int	check_arg_count(t_command *command)
{
	uint	i;

	i = 0;

	while (command->raw_args[i])
		i++;

	return (command->op->arg_number == i);
}

static int	check_args_type(t_command *command)
{
	uint	i;
	uint	ac;
	char	**args;

	i = 0;
	ac = command->op->arg_number;
	args = command->raw_args;

	while (i < ac)
	{
		args[ac] = args[i];
		args[i] = ft_strtrim(args[i]);
		free(args[ac]);
		args[ac] = NULL;

		if ((get_arg_type(args[i]) & command->op->args[i]) == 0)
			return (0);

		i++;
	}

	return (1);
}

int		parse_command(char const *line, uint row)
{
	t_command	*command;
	char		*name;

	command = malloc(sizeof(t_command));
	name = get_command_name(line);
	command->op = get_op(name);


	if (command->op == NULL)
		die2("Unknown command", row, skip_white_spaces(line) - line);

	command->raw_args = ft_strsplit(line + ft_strlen(name), SEPARATOR_CHAR);

	if (!check_arg_count(command))
		die2("Bad argument count", row, skip_white_spaces(line) - line);

	if (!check_args_type(command))
		die2("Bad argument type", row, 0);

	return (0);
}
