/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 20:59:15 by adebray           #+#    #+#             */
/*   Updated: 2015/02/05 06:02:34 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		update(int dt)
{
	static int		count;
	(void)dt;
	count += 1;
	dprintf(1, "cycle: %d\n", count);
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

	corewar_check();
	corewar_init(argc, argv);
	ncurse = 0;
	player_nbr = corewar_getopt(heros, &ncurse);

	if (ncurse)
		ncurse_init();
	if (player_nbr)
		foreach_heros(player_nbr, heros);
	ft_printf("%d champions in da plaza\n", player_nbr, ncurse);
	while (player_nbr)
	{
		update(0);
		draw(ncurse);
		usleep(800 * 3000);
		// sleep(60);
	}

	endwin();
	return (0);
}
