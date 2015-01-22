/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 07:08:17 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/22 09:03:21 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	op_tab[1];

static int	command_exists(char const *command)
{
	uint	i;

	i = 0;

	while (op_tab[i].name)
	{
		if (ft_strequ(op_tab[i].name, command))
			return (1);
		i++;
	}

	return (0);
}

static char const	**split_command(char const *line)
{
	char const	**splits;
	char const	*save;
	uint		split_count;
	uint		i;

	line = skip_white_spaces(line);

	split_count = 0;
	save = line;

	while (*line)
	{
		if (ft_isdigit(*line))
		{
			line = skip_white_spaces(line);
			split_count++;
		}

		line++;
	}

	if (split_count == 0)
		return (NULL);

	splits = malloc(sizeof(char*) * (split_count + 1));
	line = save;
	i = 0;

	while (*line)
	{
		if (ft_isdigit(*line))
		{
			splits[i++] = save;
			line = skip_white_spaces(line);
			save = line;
		}
		else
			line++;
	}

	return splits;
}

int		parse_command(char const *line, uint row)
{
	char const	**splits;

	splits = split_command(line);

	ft_putendl(splits[0]);
	ft_printf("%n", command_exists(splits[0]));

	exit(0);


	(void) row;

	return (0);
}