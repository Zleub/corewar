/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 20:59:15 by adebray           #+#    #+#             */
/*   Updated: 2015/04/29 21:07:10 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define OUT 1

#include <corewar.h>

void	die(int end)
{
	exit(end);
}

int		get_opt(int argc, char **argv)
{
	int		player_nbr;
	int		i;

	i = 1;
	player_nbr = 0;
	while (i < argc - 1)
	{
		if (!ft_strcmp(argv[i], "-n") && argv[i + 1])
		{
			get_heros(argv[i + 1]);
			player_nbr += 1;
		}
		else if (!ft_strcmp(argv[i], "-d") && argv[i + 1])
			g_corewar.dump = ft_atoi(argv[i + 1]);
		else if (!ft_strcmp(argv[i], "-v") && argv[i + 1])
			g_corewar.verb = ft_atoi(argv[i + 1]);
		else if (!ft_strcmp(argv[i], "-t") && argv[i + 1])
			g_corewar.tic_rate = ft_atoi(argv[i + 1]);
		i += 1;
	}
	return (player_nbr);
}

int		main(int argc, char **argv)
{
	// ft_bzero(&g_corewar, sizeof(t_corewar));
	g_corewar.dump = 0;
	g_corewar.verb = 0;
	g_corewar.cycle_counter = 0;
	g_corewar.tic_rate = 0;

	int i = 0;
	while (i < MAX_PLAYERS)
	{
		g_corewar.scores[i] = 0;
		i += 1;
	}

	if (CYCLE_TO_DIE != 0)
		g_corewar.cycles_todie = CYCLE_TO_DIE;
	else
		exit(-1); // ERRROR

	if (argc < 2)
	{
		write(1, "Usage : ./corewar [-d X -v X -ncurse] -n champion -n champion ...\n", 66);
		return (-1);
	}
	init_corewar(get_opt(argc, argv));
	while (42)
	{
		update(0);
		draw();
	}
	return (0);
}
