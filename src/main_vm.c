/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arno <Arno@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 20:59:15 by adebray           #+#    #+#             */
/*   Updated: 2015/01/26 14:14:38 by Arno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

t_op		g_op_tab[17];

void		write_heros(int offset, t_heros *heros)
{
	unsigned int m;
	t_memory *memory;

	m = 0;
	memory = manage_memory(GET);
	while (m < heros->h.prog_size)
	{
		memory->memory[offset + m].colorp = heros->color;
		memory->memory[offset + m].op = (unsigned char)heros->c[m];
		m += 1;
	}
	manage_process(NEW);
	manage_process(GET)->index = offset;
	memory->memory[offset].proc = 1;
	manage_process_list(ADD);
}

void		foreach_heros(int player_nbr, t_heros *heros)
{
	int			offset;
	int			i;

	i = 0;
	offset = MEM_SIZE / player_nbr;
	while (i < player_nbr)
	{
		write_heros(offset * i, &heros[i]);
		i += 1;
	}
}

void		get_op(t_process *p)
{
	t_memory		*memory;
	t_op			tmp;

	memory = manage_memory(GET);
	tmp = g_op_tab[(int)memory->memory[p->index].op - 1];

	// int i = 0;
	dprintf(2, "index: %d\n", p->index);
	// dprintf(2, "%s: arg_number: %d\n", tmp.name, tmp.arg_number);
	// while (i < tmp.arg_number)
	// {
	// 	dprintf(2, "\t-> arg: %d\n", tmp.args[i]);
	// 	i += 1;
	// }

	memory->memory[p->index].proc = 0;
	p->index += 1;
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

int			main(int argc, char **argv)
{
	int			player_nbr;
	t_heros		heros[4];

	corewar_init(argc, argv);
	player_nbr = corewar_getopt(heros);
	foreach_heros(player_nbr, heros);

	while (player_nbr)
	{
		wclear(stdscr);
		manage_memory(PRINT);
		// manage_process_list(PRINT);
		wrefresh(stdscr);

		increment_process();

		usleep(800 * 3000);
		dprintf(2, "usleep end\n");
	}

	endwin();
	return (0);
}
