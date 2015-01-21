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

#include "asm.h"

int		parse_name(char const *line, uint row)
{
	char	*occ;

	occ = ft_strchr(line, ' ');

	if (occ == NULL)
		syntax_error("You must specify a name.", row, ft_strlen(NAME_CMD_STRING));

	
	return 0;
}