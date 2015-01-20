/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 01:54:46 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/20 01:54:47 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include "asm.h"
#include "get_next_line.h"

int		parse_line(char const *line, uint lineNumber)
{
	char const	*current;

	if (line && *line == COMMENT_CHAR)
		return parse_comment(line);
	else if (ft_strstr(line, NAME_CMD_STRING))
		return parse_name(line);

	current = line;

	while (*current)
	{
		if (ft_strchr(LABEL_CHARS, *current))
			continue;
		else if (current != line && *current == LABEL_CHAR)
			parse_label(line);
		else
			invalid_char_die(lineNumber, (int)(current - line) + 1);

		current++;
	}

	return 0;
}

void		parse_file(int fd)
{
	char	*line;
	uint	i;

	i = 1;

	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line))
			parse_line(line, i);

		i++;
		free(line);
	}
}