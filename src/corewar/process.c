/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 17:08:09 by adebray           #+#    #+#             */
/*   Updated: 2015/04/22 23:52:28 by adebray          ###   ########.fr       */
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
	nbr += 1;
	if (elem)
		ft_memcpy(new, elem, sizeof(t_process));
	else
		ft_bzero(new, sizeof(t_process));
	new->number = nbr;
	return (new);
}

void		move_process(t_process *p, int size)
{
	g_memory[p->index].p = 0;
	p->index += size;
	g_memory[p->index].p = 1;
}
// void			print_process(t_process *head)
// {
// 	t_op op;

// 	op = get_op(head);
// 	if (head)
// 	{
// 		dprintf(OUT, "P\t%d | %s", head->number, op->name);
// 		// print_instruction_decimal();
// 		print_process(head->next);
// 	}
// }

void (*t[16])(t_process *);

void			update_process(t_process *head)
{
	t_op		op;

	if (!head)
		return ;
	op = get_op(head);
	(void)op;
	if (head->delay == 0)
	{
		int size = fill_instruction(head);

		dprintf(OUT, "P\t%d | %s : ", head->number, op.name);
		print_instruction_decimal();

		t[op.opcode - 1](head);

		move_process(head, size);
		op = get_op(head);
		head->delay = op.cycles;
	}
	else
	{
		head->delay -= 1;
	}
	update_process(head->next);
}
