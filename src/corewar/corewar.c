/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 18:36:41 by adebray           #+#    #+#             */
/*   Updated: 2015/04/24 15:57:29 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	draw(void)
{
	dprintf(OUT, "cycle_counter: %d\n", g_corewar.cycle_counter);
	print_process(g_process);
}

void	update(int dt)
{
	(void)dt;
	usleep(800 * 100);
	g_corewar.cycle_counter += 1;
	update_process(g_process);
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
