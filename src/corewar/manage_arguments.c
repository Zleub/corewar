/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 17:01:18 by adebray           #+#    #+#             */
/*   Updated: 2015/02/04 17:24:44 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

t_arguments		*manage_arguments(int macro)
{
	static t_arguments	current;

	if (macro == GET)
		return (&current);
	else
		ft_printf("Useless calll to manage_argumentss\n");
	return (NULL);
}
