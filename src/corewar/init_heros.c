/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_heros.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 03:49:47 by adebray           #+#    #+#             */
/*   Updated: 2015/02/05 06:07:19 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		write_heros(int offset, t_heros *heros)
{
	unsigned int m;
	t_memory *memory;

	m = 0;
	memory = manage_memory(GET);
	while (m < heros->h.prog_size)
	{
		memory->memory[offset + m].colorp = heros->color;
		memory->memory[offset + m].op = (unsigned char)heros->c[m];
		m += 1;
	}
	manage_process(NEW);
	manage_process(GET)->index = offset;
	manage_process(GET)->registers[0][REG_SIZE - 1] = heros->number;
	memory->memory[offset].proc = 1;
	manage_process_list(ADD);
	init_pair(heros->color, ft_hashich(heros->h.prog_name), COLOR_BLACK);
}

void		foreach_heros(int player_nbr, t_heros *heros)
{
	int			offset;
	int			i;

	i = 0;
	offset = MEM_SIZE / player_nbr;
	while (i < player_nbr)
	{
		ft_printf("Introducing %s, n: %d, %db of code\n", heros[i].h.prog_name, heros[i].number, heros[i].h.prog_size * 8);
		ft_printf("\t\"%s\"\n", heros[i].h.comment);
		write_heros(offset * i, &heros[i]);
		i += 1;
	}
}
