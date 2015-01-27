/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_process_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 10:00:54 by adebray           #+#    #+#             */
/*   Updated: 2015/01/26 16:36:10 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

t_process_list		*new_process_list(t_process *p)
{
	t_process_list	*new;

	if (!(new = (t_process_list *)malloc(sizeof(t_process_list))))
		return (NULL);
	new->p = p;
	return (new);
}

t_process_list		*add_process_list(t_process_list *head)
{
	t_process_list	*tmp;
	t_process *p;

	p = manage_process(GET);
	if (!head)
		head = new_process_list(p);
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_process_list(p);
	}
	return (head);
}

void			debug_process_list(t_process_list *head)
{
	if (head)
	{
		dprintf(2, "%p\n", head);
		dprintf(2, "p: %p, p->index: %d\n", head->p, head->p->index);
		debug_process_list(head->next);
	}
}

void			*manage_process_list(int macro)
{
	static t_process_list	*head;

	if (macro == ADD)
		head = add_process_list(head);
	else if (macro == PRINT)
		debug_process_list(head);
	else if (macro == GET)
		return (head);
	else
		ft_printf("Useless call to manage_process_list\n");
	return (NULL);
}
