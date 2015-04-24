/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 20:59:15 by adebray           #+#    #+#             */
/*   Updated: 2015/04/24 19:57:55 by adebray          ###   ########.fr       */
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
		i += 1;
	}
	return (player_nbr);
}

int		main(int argc, char **argv)
{
	g_corewar.dump = 0;
	g_corewar.verb = 0;
	g_corewar.cycle_counter = 0;
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
