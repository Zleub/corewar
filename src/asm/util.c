/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 01:54:46 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/25 16:17:48 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <libft.h>
#include <ft_printf.h>

void	die(char const *message)
{
	ft_putendl(message);
	exit(EXIT_SUCCESS);
}

void	die2(char *message, uint line, uint col)
{
	uint	i;
	char	*l;

	ft_printf("Error at line %u, column %u : %s.\n", line, col, message);
	l = get_current_line(0);
	ft_putendl(l);
	i = 0;
	while (i < col)
	{
		if (l[i] == '\t')
			ft_putstr("\t");
		else
			ft_putchar('.');
		i++;
	}
	ft_putendl("^\n");
	exit(EXIT_SUCCESS);
}

char	*skip_white_spaces(char const *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return ((char*)str);
}

int		is_number(char const *str)
{
	if (*str == '-')
		str++;
	while (*str != 0)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
