/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 21:11:58 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/28 03:10:27 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char const	*parse_label(char const *line, uint row)
{
	char		*occ;

	occ = ft_strchr(line, LABEL_CHAR);
	add_label(ft_strndup((char*)line, occ - line));
	occ++;
	while (*occ)
	{
		if (!ft_isspace(*occ))
			return (occ);
			// die2("Unexpected character", row, occ - line);
		occ++;
	}
	return (NULL);
	(void)row;
}
