/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_comment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 21:11:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/25 16:17:41 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		parse_comment(char const *line, uint row)
{
	char		*occ;
	char const	*save;

	occ = ft_strchr(line, '"');
	if (occ == NULL)
		die2("You must specify a comment.", row, ft_strlen(COMMENT_CMD_STRING));
	save = line;
	line = occ + 1;
	while (*line != '"')
	{
		if (*line == '\0')
			die2("Unclosed quote", row, ft_strchr(save, '"') - save);
		else if (line - occ > COMMENT_LENGTH)
			die2("The comment is too long", row, line - save);
		line++;
	}
	get_champion(0)->comment = ft_strdup(save);
	return (0);
}
