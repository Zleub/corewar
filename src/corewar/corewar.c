/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 18:36:41 by adebray           #+#    #+#             */
/*   Updated: 2015/05/14 07:55:01 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	print_scores(void)
{
	int i = 0;
	while (i < g_corewar.player_nbr)
	{
		dprintf(OUT, "n%d [%s] : %d\n", i, g_heros[i].head.prog_name, g_corewar.scores[i]);
		i += 1;
	}
}

void	end(void)
{
	dprintf(OUT, "no more process alive, exit\n");
	if (g_corewar.last_alive == 0)
		dprintf(OUT, "No one said live ... dumbass\n");
	else
		dprintf(OUT, "Winner is %d, %s\n", g_corewar.last_alive, g_heros[g_corewar.last_alive - 1].head.prog_name);
	print_scores();
	exit(EXIT_SUCCESS);
}

void	draw(void)
{
	if (g_corewar.verb > 2)
	{
		dprintf(OUT, "cycle_counter: %d\n", g_corewar.cycle_counter);
		dprintf(OUT, "cycle_counter %% cycle_to_die: %d\n", g_corewar.cycle_counter % g_corewar.cycles_todie);
		dprintf(OUT, "cycle_to_die: %d\n", g_corewar.cycles_todie);
		print_scores();
		print_process(g_process);
	}
}

int		removedead(t_process *tmp)
{
	int			live_nbr;
	t_process	*p;

	p = tmp;
	live_nbr = p->lives;
	p->lives = 0;
	while (p != NULL)
	{
		if (!p->next)
			return (live_nbr);
		tmp = p->next;
		if (tmp->lives == 0)
		{
			p->next = tmp->next;
			g_corewar.process_nbr -= 1;
			dprintf(OUT, "removing N_%d\n", tmp->number);
			free(tmp);
		}
		live_nbr += p->lives;
		p->lives = 0;
		p = p->next;
	}
	return (live_nbr);
}

int		inspect(void)
{
	t_process *p;
	t_process *tmp;

	p = g_process;
	while (p && p->lives == 0)
	{
		tmp = p;
		p = p->next;
		g_corewar.process_nbr -= 1;
		dprintf(OUT, "removing N_%d process\n", tmp->number);
		free(tmp);
	}
	g_process = p;
	if (g_process == NULL)
		end();
	return (removedead(p));
}

void	update(int dt)
{
	static int		check_nbr;

	(void)dt;
	if (g_corewar.tic_rate != 0)
		usleep(800 * g_corewar.tic_rate);
	g_corewar.cycle_counter += 1;
	update_process(g_process);
	if (g_corewar.cycle_counter % g_corewar.cycles_todie == 0)
	{
		if (inspect() >= NBR_LIVE || check_nbr >= MAX_CHECKS)
		{
			g_corewar.cycles_todie -= CYCLE_DELTA;
			dprintf(OUT, "g_corewar.cycles_todie: %d : %d\n", g_corewar.cycles_todie, g_corewar.process_nbr);
			check_nbr = 0;
		}
		check_nbr += 1;
	}
	if (g_corewar.cycle_counter == g_corewar.dump)
	{
		dump_memory();
		exit(EXIT_SUCCESS);
	}
	else if (g_corewar.cycles_todie < 0)
		exit(EXIT_SUCCESS);
}

int		max_size(void)
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
	init_array();
	return (player_nbr);
}
