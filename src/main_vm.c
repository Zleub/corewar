/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 20:59:15 by adebray           #+#    #+#             */
/*   Updated: 2015/01/25 16:00:02 by adebray          ###   ########.fr       */
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

void		increment_process(void)
{
	t_process_list	*head;
	t_memory		*memory;

	head = manage_process_list(GET);
	memory = manage_memory(GET);
	while (head)
	{
		t_op test = g_op_tab[(int)memory->memory[head->p->index].op - 1];

		int i = 0;

		dprintf(2, "%s: arg_number: %d\n", test.name, test.arg_number);
		while (i < test.arg_number)
		{
			dprintf(2, "\t-> arg: %d\n", test.args[i]);
			i += 1;
		}

		memory->memory[head->p->index].proc = 0;
		head->p->index += 1;
		memory->memory[head->p->index].proc = 1;

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
