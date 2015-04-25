/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 17:08:09 by adebray           #+#    #+#             */
/*   Updated: 2015/04/25 13:12:42 by adebray          ###   ########.fr       */
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
	new->carry = 0;
	return (new);
}

void		move_process(t_process *p, int size)
{
	g_memory[p->index].p = 0;
	p->index += size;
	g_memory[p->index].p = 1;
}

void			print_registers(t_process * p)
{
	int i = 0;
	int j = 0;
	while (i < REG_NUMBER)
	{
		j = 0;
		ft_printf("\t\tr[%d]:\t", i);
		while (j < REG_SIZE && g_corewar.verb >= 3)
		{
			write(1, "[", 1);
			print_clean_hexa(p->registers[i][j]);
			write(1, "]", 1);
			j += 1;
		}
		write(1, "\n", 1);
		i += 1;
	}
}

void			print_process(t_process *head)
{
	t_op	op;

	if (head)
	{
		op = get_op(head);
		if (g_corewar.verb >= 2)
		{
			dprintf(OUT, "\t%d @ %d to %d | %s \n", head->number, head->index, head->pc, op.name);
			dprintf(OUT, "\t\tpc: [%d], carry: [%d], delay: [%d] \n", head->pc, head->carry , head->delay);
		}
		if (g_corewar.verb >= 3)
			print_registers(head);
		print_process(head->next);
	}
}

void			execute_process(t_process *head, t_op *op)
{
	extern void	(*t[16])(t_process *);
	int size;

	if (g_corewar.verb >= 2)
	{
		dprintf(OUT, " \t%d @ %d | %s : ", head->number, head->index, op->name);
		print_instruction_decimal();
	}

	size = fill_instruction(head);
	t[op->opcode - 1](head);

	move_process(head, size);
	*op = get_op(head);
	head->delay = op->cycles;
}

void			update_process(t_process *head)
{
	t_op		op;

	if (!head)
		return ;
	op = get_op(head);
	if (op.name == 0)
	{
		move_process(head, 1);
		update_process(head->next);
		return ;
	}
	head->delay -= 1;
	if (head->delay == 0)
		execute_process(head, &op);
	update_process(head->next);
}
