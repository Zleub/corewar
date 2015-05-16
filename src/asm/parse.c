/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 01:54:46 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/16 03:16:36 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include "asm.h"
#include "get_next_line.h"

static void	check_champion_validity(t_champion *champion)
{
	if (champion->name == NULL)
		die("The champion must have a name.");
	if (champion->comment == NULL)
		die("The champion must have a comment.");
}

int		parse_line(char const *line, uint row)
{
	char const	*current;

	if ((current = line) && line && *line == COMMENT_CHAR)
		return (0);
	else if (ft_strstr(line, NAME_CMD_STRING))
		return (parse_name(line, row));
	else if (ft_strstr(line, COMMENT_CMD_STRING))
		return (parse_comment(line, row));
	while (*current)
	{
		if (!ft_strchr(LABEL_CHARS, *current))
		{
			if (current != line && *current == LABEL_CHAR)
			{
				if ((current = parse_label(line, row)))
					return parse_line(current, row);
				return (0);
			}
			else
				return (parse_command(line, row));
		}
		current++;
	}
	die2("Unknown command", row, 0);
	return (0);
}

void	parse_file(int fd)
{
	char	*line;
	char	*trimmed;
	uint	i;

	i = 1;
	while (get_next_line(fd, &line) > 0)
	{
		if (line && (trimmed = ft_strchr(line, ';')))
		{
			trimmed = ft_strsub(line, 0, trimmed - line);
			ft_putendl(trimmed);
			free(line);
			line = trimmed;
		}
		trimmed = ft_strtrim(line);
		free(line);
		get_current_line(trimmed);
		if (ft_strlen(trimmed))
			parse_line(trimmed, i);
		i++;
		free(trimmed);
	}
	check_champion_validity(get_champion(0));
}

char	*get_current_line(char *line)
{
	static char	*l;

	if (line)
		l = line;
	return (l);
}
