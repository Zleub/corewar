/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 20:59:15 by adebray           #+#    #+#             */
/*   Updated: 2015/05/08 15:14:23 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define OUT 1

#include <corewar.h>

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

	if (CYCLE_TO_DIE != 0)
		g_corewar.cycles_todie = CYCLE_TO_DIE;
	else
		exit(EXIT_FAILURE); // ERRROR

	if (argc < 2)
	{
		write(1, "Usage : ./corewar [-d X -v X -ncurse] -n champion -n champion ...\n", 66);
		return (EXIT_FAILURE);
	}
	g_corewar.player_nbr = init_corewar(get_opt(argc, argv));
	dprintf(OUT, "player_nbr = %d\n", g_corewar.player_nbr);
	if (!(g_corewar.scores = (unsigned int *)malloc(sizeof(unsigned int) * g_corewar.player_nbr)))
		return (EXIT_FAILURE);
	ft_bzero(g_corewar.scores, sizeof(unsigned int) * g_corewar.player_nbr);
	while (42)
	{
		update(0);
		draw();
	}
	return (EXIT_SUCCESS);
}
