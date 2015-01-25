/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 10:02:59 by adebray           #+#    #+#             */
/*   Updated: 2015/01/25 14:20:53 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

t_process		*new_process(void)
{
	t_process	*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
		return (NULL);
	new->index = 0;
	return (new);
}

t_process		*manage_process(int macro)
{
	static t_process	*current;

	if (macro == NEW)
		current = new_process();
	else if (macro == GET)
		return (current);
	else
		ft_printf("Useless call to manage_process\n");
	return (NULL);
}
