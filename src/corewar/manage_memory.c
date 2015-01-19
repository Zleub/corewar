/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 23:46:21 by adebray           #+#    #+#             */
/*   Updated: 2015/01/19 23:54:19 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*new_memory(t_memory *memory)
{
	memory->size = MEM_SIZE;
	ft_bzero(memory->memory);
}

void		manage_memory(int macro)
{
	static t_memory		memory;

	if (macro == NEW)
		memory = new_memory(&memory);
}
