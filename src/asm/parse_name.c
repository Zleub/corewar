/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 01:54:46 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/28 03:04:27 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		parse_name(char const *line, uint row)
{
	char		*occ;
	char const	*save;

	occ = ft_strchr(line, '"');
	if (occ == NULL)
		die2("You must specify a name.", row, ft_strlen(COMMENT_CMD_STRING));
	save = line;
	line = occ + 1;
	while (*line != '"')
	{
		if (*line == '\0')
			die2("Unclosed quote", row, ft_strchr(save, '"') - save);
		else if (line - occ > COMMENT_LENGTH)
			die2("The name is too long", row, line - save);
		line++;
	}
	occ++;
	get_champion(0)->name = ft_strndup(occ, ft_strchr(occ, '"') - occ);
	return (0);
}
