/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 20:59:15 by adebray           #+#    #+#             */
/*   Updated: 2015/01/24 02:05:14 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		write_herostomemory(int offset, t_heros *heros)
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
}

int			main(int argc, char **argv)
{
	int			player_nbr;
	t_heros		heros[4];

	corewar_init(argc, argv);
	player_nbr = corewar_getopt(heros);

	int offset = MEM_SIZE / player_nbr;
	int i = 0;
	while (i < player_nbr)
	{
		write_herostomemory(offset * i, &heros[i]);
		i += 1;
	}

	manage_memory(PRINT);
	wrefresh(stdscr);

	sleep(60);
	endwin();
	return (0);
}
