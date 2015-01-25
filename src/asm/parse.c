/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 01:54:46 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/25 16:19:16 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include "asm.h"
#include "get_next_line.h"

int		parse_line(char const *line, uint row)
{
	char const	*current;

	if (line && *line == COMMENT_CHAR)
		return (0);
	else if (ft_strstr(line, NAME_CMD_STRING))
		return (parse_name(line, row));
	else if (ft_strstr(line, COMMENT_CMD_STRING))
		return (parse_comment(line, row));
	current = line;
	while (*current)
	{
		if (!ft_strchr(LABEL_CHARS, *current))
		{
			if (current != line && *current == LABEL_CHAR)
				return (parse_label(line, row));
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
		trimmed = ft_strtrim(line);
		free(line);
		get_current_line(trimmed);
		if (ft_strlen(trimmed))
			parse_line(trimmed, i);
		i++;
		free(trimmed);
	}
	get_champion(1);
}

char	*get_current_line(char *line)
{
	static char	*l;

	if (line)
		l = line;
	return (l);
}
