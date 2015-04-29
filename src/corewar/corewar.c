/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 18:36:41 by adebray           #+#    #+#             */
/*   Updated: 2015/04/29 21:20:20 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	draw(void)
{
	if (g_corewar.verb > 2)
	{
		dprintf(OUT, "cycle_counter: %d\n", g_corewar.cycle_counter);
		dprintf(OUT, "cycle_counter %% CYCLE_TO_DIE: %d\n", g_corewar.cycle_counter % g_corewar.cycles_todie);
		dprintf(OUT, "CYCLE_TO_DIE: %d\n", g_corewar.cycles_todie);
		int i = 0;
		while (i < MAX_PLAYERS)
		{
			dprintf(OUT, "n%d : %d\n", i, g_corewar.scores[i]);
			i += 1;
		}
		// print_process(g_process);
	}
}

void	update(int dt)
{
	(void)dt;
	if (g_corewar.tic_rate != 0)
		usleep(800 * g_corewar.tic_rate);
	g_corewar.cycle_counter += 1;
	update_process(g_process);
	if (g_corewar.cycle_counter % g_corewar.cycles_todie == 0)
	{
		;
	}
	if (g_corewar.cycle_counter == g_corewar.dump)
	{
		dump_memory();
		die(0);
	}
}

int		max_size()
{
	int		max;

	max = 0;
	if (REG_SIZE > IND_SIZE)
		max = REG_SIZE;
	else
		max = IND_SIZE;

	if (DIR_SIZE > max)
		max = DIR_SIZE;
	return (max);
}

void	init_corewar(int player_nbr)
{
	g_process = NULL;
	init_memory(player_nbr);
	init_instruction(max_size());
}
