/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 23:46:21 by adebray           #+#    #+#             */
/*   Updated: 2015/01/20 08:03:57 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include <op.h>
#include <corewar.h>

static void		new_memory(t_memory *memory)
{
	memory->size = MEM_SIZE;
	memory->memory = (char*)malloc(sizeof(char) * memory->size);
	ft_bzero(memory->memory, MEM_SIZE);
}

static void		print_memory(t_memory *memory)
{
	int			index;

	index = 0;
	ft_printf("size: %d\n", memory->size);
	while (index < memory->size)
	{
		ft_printf(" 0%x ", memory->memory[index]);
		if (index % (IDX_MOD / 8) == (IDX_MOD / 8) - 1)
			ft_printf("\n");
		index += 1;
	}
	ft_printf("\n");
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
