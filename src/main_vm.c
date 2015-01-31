/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 20:59:15 by adebray           #+#    #+#             */
/*   Updated: 2015/01/31 14:40:34 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		update(int dt)
{
	(void)dt;
	increment_process();
}

void		draw(char ncurse)
{
	if (ncurse)
	{
		wclear(stdscr);
		manage_memory(PRINT);
		wrefresh(stdscr);
	}
}

int			main(int argc, char **argv)
{
	int			player_nbr;
	int			ncurse;
	t_heros		heros[4];

	corewar_init(argc, argv);
	ncurse = 0;
	player_nbr = corewar_getopt(heros, &ncurse);

	if (ncurse)
		ncurse_init();
	if (player_nbr)
		foreach_heros(player_nbr, heros);
	ft_printf("%d..%d\n", player_nbr, ncurse);
	while (player_nbr)
	{
		update(0);
		draw(ncurse);
		usleep(800 * 3000);
		// sleep(60);
		dprintf(2, "usleep end\n");
	}

	endwin();
	return (0);
}
