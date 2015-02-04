/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 23:46:21 by adebray           #+#    #+#             */
/*   Updated: 2015/02/04 03:20:29 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include <corewar.h>

static void		new_memory(t_memory *memory)
{
	memory->size = MEM_SIZE;
	memory->memory = (t_cell*)malloc(sizeof(t_cell) * memory->size);
	ft_bzero(memory->memory, MEM_SIZE * sizeof(t_cell));
}

static void		init_memory(t_memory *memory)
{
	memory->memory_callbacks[0] = init_memory;
	memory->memory_callbacks[1] = new_memory;
	memory->memory_callbacks[2] = print_memory;
}

t_memory		*manage_memory(int macro)
{
	static t_memory		memory;

	if (macro == INIT)
		init_memory(&memory);
	else if (macro == NEW)
		(*memory.memory_callbacks[1])(&memory);
	else if (macro == PRINT)
		(*memory.memory_callbacks[2])(&memory);
	else if (macro == GET)
		return (&memory);
	else
		ft_printf("useless call to manage_memory\n");
	return (NULL);
}
