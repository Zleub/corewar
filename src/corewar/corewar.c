/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 18:36:41 by adebray           #+#    #+#             */
/*   Updated: 2015/05/04 18:04:18 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	print_scores(void)
{
	int i = 0;
	while (i < g_corewar.player_nbr)
	{
		dprintf(OUT, "n%d : %d\n", i, g_corewar.scores[i]);
		i += 1;
	}
}

void	end(void)
{
	dprintf(OUT, "no more process alive, exit\n");
	dprintf(OUT, "Winner is %d, %s\n", g_corewar.last_alive, g_heros[g_corewar.last_alive - 1].head.prog_name);
	print_scores();
	exit(-1);
}

void	draw(void)
{
	if (g_corewar.verb > 2)
	{
		dprintf(OUT, "cycle_counter: %d\n", g_corewar.cycle_counter);
		dprintf(OUT, "cycle_counter %% cycle_to_die: %d\n", g_corewar.cycle_counter % g_corewar.cycles_todie);
		dprintf(OUT, "cycle_to_die: %d\n", g_corewar.cycles_todie);
		print_scores();
		// print_process(g_process);
	}
}

void	removedead(t_process *tmp)
{
	t_process *p;

	p = tmp;
	p->lives = 0;
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

void	inspect(void)
{
	t_process *p;
	t_process *tmp;

	p = g_process;
	while (p && p->lives == 0)
	{
		tmp = p;
		p = p->next;
		dprintf(OUT, "removing N_%d process\n", tmp->number);
		free(tmp);
	}
	g_process = p;
	if (g_process == NULL)
		end();
	removedead(p);
}

void	update(int dt)
{
	(void)dt;
	if (g_corewar.tic_rate != 0)
		usleep(800 * g_corewar.tic_rate);
	g_corewar.cycle_counter += 1;
	update_process(g_process);
	if (g_corewar.cycle_counter % g_corewar.cycles_todie == 0)
		inspect();
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
