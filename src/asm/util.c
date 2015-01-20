/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 01:54:46 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/20 01:54:47 by amaurer          ###   ########.fr       */
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

void	invalid_char_die(uint line, uint col)
{
	ft_printf("Invalid character at line %u, column %u\n", line, col);

	exit(EXIT_SUCCESS);
}