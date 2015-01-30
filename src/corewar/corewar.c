/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/29 17:58:38 by adebray           #+#    #+#             */
/*   Updated: 2015/01/29 18:14:00 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

t_op		g_op_tab[17];

void		get_op(t_process *p)
{
	t_memory		*memory;
	t_op			tmp;

	memory = manage_memory(GET);
	tmp = g_op_tab[(int)memory->memory[p->index].op - 1];


	int size = 1;
	if (tmp.coding_octet == 0)
	{
		dprintf(2, "index: %d\n", p->index);
		dprintf(2, "__%s__: arg_number: %d\n", tmp.name, tmp.arg_number);

		if (tmp.args[0] == 1)
			size += 1;
		else
			size += 2;

		memory->memory[p->index].proc = 0;
		p->index += size;
		memory->memory[p->index].proc = 1;
		return ;
	}
	else
		size += 1;

	dprintf(2, "index: %d\n", p->index);
	dprintf(2, "__%s__: arg_number: %d\n", tmp.name, tmp.arg_number);

	int i = 0;
	while (i < tmp.arg_number)
	{
		dprintf(2, "args[%d]: %d\n", i, tmp.args[i]);
		if (tmp.args[i] == 1)
			size += 1;
		else if (tmp.args[i] == 6)
			size += 4;
		else
			size += 2;
		i += 1;
	}

	dprintf(2, "size: %d\n", size);

	memory->memory[p->index].proc = 0;
	p->index += size;
	memory->memory[p->index].proc = 1;
}

void		increment_process(void)
{
	t_process_list	*head;

	head = manage_process_list(GET);
	while (head)
	{
		get_op(head->p);
		// sleep(60);
		head = head->next;
	}
}

void		ncurse_init(void)
{
	stdscr = initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	assume_default_colors(235, COLOR_BLACK);
}
