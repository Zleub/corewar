/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 18:36:41 by adebray           #+#    #+#             */
/*   Updated: 2015/05/01 01:58:47 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	draw(void)
{
	if (g_corewar.verb > 2)
	{
		dprintf(OUT, "cycle_counter: %d\n", g_corewar.cycle_counter);
		dprintf(OUT, "cycle_counter %% cycle_to_die: %d\n", g_corewar.cycle_counter % g_corewar.cycles_todie);
		dprintf(OUT, "cycle_to_die: %d\n", g_corewar.cycles_todie);
		int i = 0;
		while (i < g_corewar.player_nbr)
		{
			dprintf(OUT, "n%d : %d\n", i, g_corewar.scores[i]);
			i += 1;
		}
		// print_process(g_process);
	}
}

void	inspect(void)
{
	t_process *p;
	t_process *tmp;

	dprintf(OUT, "inspect : %d\n", g_process->lives);
	p = g_process;
	while (p && p->lives == 0)
	{
		tmp = p;
		p = p->next;
		free(tmp);
	}
	g_process = p;

	if (g_process == NULL)
	{
		dprintf(OUT, "no more process alive, exit\n");
		exit(-1);
	}

	while (p != NULL)
	{
		if (!p->next)
			return ;
		tmp = p->next;
		dprintf(OUT, "tmp: %d\n", tmp->lives);
		if (tmp->lives == 0)
		{
			p->next = tmp->next;
			dprintf(OUT, "removing N_%d\n", tmp->number);
			free(tmp);
		}
		p->lives = 0;
		p = p->next;
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
		int i = 0;
		int j = 0;
		while (i < g_corewar.player_nbr)
		{
			if (g_corewar.scores[i] > NBR_LIVE)
				j = 1;
			g_corewar.scores[i] = 0;
			i += 1;
		}
		if (j == 1)
			g_corewar.cycles_todie -= CYCLE_DELTA;
		inspect();
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

int		init_corewar(int player_nbr)
{
	g_process = NULL;
	init_memory(player_nbr);
	init_instruction(max_size());
	return (player_nbr);
}
