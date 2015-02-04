/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 17:58:38 by adebray           #+#    #+#             */
/*   Updated: 2015/02/04 21:37:05 by adebray          ###   ########.fr       */
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

int			get_coding_octet(t_process *p)
{
	int			coding_octet;
	t_memory	*memory;

	memory = manage_memory(GET);
	coding_octet = (int)memory->memory[p->index + 1].op;
	dprintf(1, "coding_octet: %d\n", coding_octet);
	return (coding_octet);
}

void		fill_arguments(int count, int tmpsize, t_arguments *t, t_process *p)
{
	t_memory	*memory;

	dprintf(1, " -> fill_arguments %d by %d\n", count, tmpsize);
	memory = manage_memory(GET);
	if (count == 1)
		t->first = (int)memory->memory[p->index + 2].op;
	// else if (count == 2)
}

int			get_spesize(int simple, int magic)
{
	if (simple == REG_CODE)
	{
		dprintf(1, "REG_SIZE");
		return (REG_ENCODING_SIZE);
	}
	else if (simple == DIR_CODE)
	{
		dprintf(1, "DIR_SIZE");
		if (magic == 1)
			return (DIR_ENCODING_SIZE / 2);
		else
			return (DIR_ENCODING_SIZE);
	}
	else if (simple == IND_CODE)
	{
		dprintf(1, "IND_SIZE");
		return (IND_ENCODING_SIZE);
	}
	return (-1);
}

int			get_size(unsigned char coding_octet, int magic, t_process *p)
{
	int size = 0;
	int tmpsize = 0;
	int i = 1;
	int count = 0;

	while (i != 0)
	{
		i = 0;
		i = coding_octet >> 6;
		if (i != 0)
		{
			count += 1;
			dprintf(1, "%d -> ", size);
			tmpsize = get_spesize(i, magic);
			size += tmpsize;
			dprintf(1, " -> %d\n", size);
			fill_arguments(count, tmpsize, manage_arguments(GET), p);
			coding_octet = coding_octet << 2;
		}
	}
	return (size);
}

void		do_thing(t_process *p)
{
	int				size;
	t_op			tmp;
	t_arguments		*args;

	tmp = get_op(p);
	args = manage_arguments(GET);

	dprintf(1, "P\t%d | %s ... magic: %d\n", p->number, tmp.name, tmp.unknown1);

	size = 1;

	if (tmp.coding_octet == 0)
	{
		size += get_spesize(tmp.args[0], tmp.unknown1);
		fill_arguments(1, size - 1, args, p);
	}
	else
	{
		size += 1;
		size += get_size(get_coding_octet(p), tmp.unknown1, p);
	}

	dprintf(1, "size: %d\n", size);
	dprintf(1, "args.first %d\n", args->first);
	dprintf(1, "args.second %d\n", args->second);
	dprintf(1, "args.third %d\n", args->third);
	move_process(p, size);
}

void		print_register(unsigned char *reg)
{
	int		i = 0;

	while (i < REG_SIZE)
	{
		dprintf(1, "%d", reg[i]);
		i += 1;
	}
	dprintf(1, " ");
}

void		print_registers(t_process *p)
{
	int		i = 0;

	while (i < REG_NUMBER)
	{
		print_register(p->registers[i]);
		i += 1;
	}
	dprintf(1, " \n");
}

void		increment_process(void)
{
	t_process_list	*head;

	head = manage_process_list(GET);
	while (head)
	{
		print_registers(head->p);
		do_thing(head->p);
		// sleep(60);
		head = head->next;
	}
}
