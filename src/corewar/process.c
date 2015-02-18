/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 17:08:09 by adebray           #+#    #+#             */
/*   Updated: 2015/02/18 18:35:33 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void			add_process(t_process *elem)
{
	if (!g_process)
		g_process = elem;
	else
	{
		elem->next = g_process;
		g_process = elem;
	}
}

t_process		*new_process(t_process *elem)
{
	static int	nbr;
	t_process	*new;

	if (!(new = malloc(sizeof(t_process))))
		die(-1);
	if (elem)
		ft_memcpy(new, elem, sizeof(t_process));
	else
		ft_bzero(new, sizeof(t_process));
	new->number = nbr;
	nbr += 1;
	return (new);
}

void			print_process(t_process *head)
{
	if (head)
	{
		dprintf(OUT, "process: %p n%d\n", head, head->number);
		print_process(head->next);
	}
}
