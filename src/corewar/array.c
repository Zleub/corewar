/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 17:04:33 by adebray           #+#    #+#             */
/*   Updated: 2015/05/14 16:20:36 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>




void		init_array(void)
{
	int		i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		if (!(g_array[i] = (char *)malloc(sizeof(DIR_SIZE))))
			exit(EXIT_FAILURE);
		i += 1;
	}
}

void		reset_array(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		j = 0;
		while (j < DIR_SIZE)
		{
			g_array[i][j] = 0;
			j += 1;
		}
		i += 1;
	}
}

void		fill_array(t_process *p)
{
	int		i;

	i = 0;
	reset_array();
	while (i < MAX_ARGS_NUMBER)
	{
		if (g_instruction[i].type == REG_CODE)
			cpy_register(p, &g_instruction[i], g_array[i]);
		else if (g_instruction[i].type == IND_CODE)
			cpy_memory(p, &g_instruction[i], g_array[i]);
		else if (g_instruction[i].type == DIR_CODE)
			cpy_value(p, &g_instruction[i], g_array[i]);
		i += 1;
	}

	// int j;
	// i = 0;
	// while (i < MAX_ARGS_NUMBER)
	// {
	// 	j = 0;
	// 	while (j < DIR_SIZE)
	// 	{
	// 		dprintf(OUT, "[%x]", (unsigned char)g_array[i][j]);
	// 		j += 1;
	// 	}
	// 	dprintf(OUT, "\n");
	// 	i += 1;
	// }
}
