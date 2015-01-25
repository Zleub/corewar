/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 21:11:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/25 16:17:43 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		parse_label(char const *line, uint row)
{
	char		*occ;

	occ = ft_strchr(line, LABEL_CHAR);
	add_label(ft_strndup((char*)line, occ - line));
	occ++;
	while (*occ)
	{
		if (!ft_isspace(*occ))
			die2("Unexpected character", row, occ - line);
		occ++;
	}
	return (0);
}
