/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 20:59:15 by adebray           #+#    #+#             */
/*   Updated: 2015/02/17 12:27:35 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define OUT 1

#include <corewar.h>

void	print_external(void);

static char	*cst = "Hello World";

int		main(void)
{
	extern char *cst;

	dprintf(OUT, "%s\n", cst);
	print_external();
	return (0);
}
