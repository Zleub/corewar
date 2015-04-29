/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 07:08:17 by amaurer           #+#    #+#             */
/*   Updated: 2015/04/30 00:31:19 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op		g_op_tab[17];

static t_op	*get_op(char const *command)
{
	uint	i;

	i = 0;
	while (g_op_tab[i].name)
	{
		if (ft_strequ(g_op_tab[i].name, command))
			return (&(g_op_tab[i]));
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
	return (ft_strndup((char *)save, line - save));
}

static int	get_arg_type(char const *arg)
{
	if (!arg)
		return (0);
	if (arg[0] == 'r')
		return (T_REG);
	else if (arg[0] == DIRECT_CHAR)
		return (T_DIR);
	else if (is_number(arg) || arg[0] == LABEL_CHAR)
		return (T_IND);
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

static int	parse_args_type(t_command *command)
{
	uint	i;
	uint	ac;
	char	**args;

	i = 0;
	ac = command->op->arg_number;
	args = command->raw_args;
	command->coding_octet = 0;
	while (i < ac)
	{
		args[ac] = args[i];
		args[i] = ft_strtrim(args[i]);
		free(args[ac]);
		args[ac] = NULL;
		if ((get_arg_type(args[i]) & command->op->args[i]) == 0)
			return (0);
		command->coding_octet |= get_arg_type(args[i]) << ((ac - i - 1) * 2);
		i++;
	}
	return (1);
}

#include <stdio.h>

static void	set_size(t_command *command)
{
	uint	i;
	uint	ac;
	int		type;

	command->size = 1;

	if (command->op->coding_octet)
		command->size += 1;

	ac = command->op->arg_number;
	i = 0;
	while (i < ac)
	{
		type = command->coding_octet >> (ac - i - 1);
		type &= 3;

		printf("%i\n", type);

		if (type == REG_CODE)
			command->size += REG_SIZE;
		else if (type == IND_CODE)
			command->size += IND_SIZE;
		else if (type == DIR_CODE)
		{
			if (command->op->unknown1)
				command->size += DIR_SIZE / 2;
			else
				command->size += DIR_SIZE;
		}

		i++;
	}
}

int			parse_command(char const *line, uint row)
{
	t_command	*command;
	char		*name;
	t_label		*label;

	command = malloc(sizeof(t_command));
	name = get_command_name(line);
	command->op = get_op(name);
	if (command->op == NULL)
		die2("Unknown command", row, skip_white_spaces(line) - line);
	command->raw_args = ft_strsplit(line + ft_strlen(name), SEPARATOR_CHAR);
	if (!check_arg_count(command))
		die2("Bad argument count", row, skip_white_spaces(line) - line);
	if (!parse_args_type(command))
		die2("Bad argument type", row, 0);
	command->next = NULL;
	add_command(command);
	label = get_last_label();
	if (label && !label->target)
		label->target = command;
	set_size(command);
	return (0);
}
