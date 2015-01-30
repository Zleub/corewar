/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 20:59:15 by adebray           #+#    #+#             */
/*   Updated: 2015/01/29 18:14:01 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		update(int dt)
{
	(void)dt;
	increment_process();
}

void		draw(void)
{
	wclear(stdscr);
	manage_memory(PRINT);
	wrefresh(stdscr);
}

int			main(int argc, char **argv)
{
	int			player_nbr;
	t_heros		heros[4];

	corewar_init(argc, argv);
	player_nbr = corewar_getopt(heros);

	if (player_nbr)
	{
		ncurse_init();
		foreach_heros(player_nbr, heros);
	}

	while (player_nbr)
	{
		update(0);
		draw();
		usleep(800 * 3000);
		// sleep(60);
		dprintf(2, "usleep end\n");
	}

	endwin();
	return (0);
}
