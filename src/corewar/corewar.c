/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 17:58:38 by adebray           #+#    #+#             */
/*   Updated: 2015/02/04 05:50:31 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

t_op		g_op_tab[17];

void		move_process(t_process *p, int size)
{
	t_memory		*memory;

	memory = manage_memory(GET);
	memory->memory[p->index].proc = 0;
	p->index += size;
	memory->memory[p->index].proc = 1;
}

t_op		get_op(t_process *p)
{
	int				op_index;
	t_memory		*memory;

	memory = manage_memory(GET);
	op_index = (int)memory->memory[p->index].op;
	if (op_index > 15 || op_index < 0)
	{
		dprintf(1, "error op_index: %d\n", op_index);
		exit(0);
	}
	return (g_op_tab[op_index - 1]);
}

int				get_coding_octet(t_process *p)
{
	int			coding_octet;
	t_memory	*memory;

	memory = manage_memory(GET);
	coding_octet = (int)memory->memory[p->index + 1].op;
	dprintf(1, "coding_octet: %d\n", coding_octet);
	return (coding_octet);
}

struct		s_test
{
	int		first;
	int		second;
	int		third;
};

int			get_spesize(int simple, int magic)
{
	if (simple == 1)
		return (REG_SIZE);
	else if (simple == 2)
	{
		if (magic == 1)
			return (DIR_SIZE / 2);
		else
			return (DIR_SIZE);
	}
	else if (simple == 4)
		return (IND_SIZE);
	return (-1);
}

int			get_size(unsigned char coding_octet, int magic)
{
	int size = 0;
	int i = 1;

	while (i != 0)
	{
		i = 0;
		i = coding_octet >> 6;
		dprintf(1, "i: %d\n", i);
		if (i != 0)
		{
			size += get_spesize(i, magic);
			coding_octet = coding_octet << 2;
		}
	}
	return (size);
}

void		do_thing(t_process *p)
{
	// int				dir_size;
	int				size;
	t_op			tmp;

	tmp = get_op(p);

	dprintf(1, "P\t%d | %s ... magic: %d\n", p->number, tmp.name, tmp.unknown1);
	dprintf(1, "opcode: %d\n", tmp.coding_octet);

	// struct s_test	prout;

	size = 1;
	// if (tmp.unknown1 == 1)
	// 	dir_size = 2;
	// else
	// 	dir_size = 4;

	if (tmp.coding_octet == 0)
	{
		size += get_spesize(tmp.args[0], tmp.unknown1);
	}
	else
	{
		size += 1;
		size += get_size(get_coding_octet(p), tmp.unknown1);
	}

	dprintf(1, "size: %d\n", size);
	move_process(p, size);
}

void		increment_process(void)
{
	t_process_list	*head;

	head = manage_process_list(GET);
	while (head)
	{
		do_thing(head->p);
		// sleep(60);
		head = head->next;
	}
}
