/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 23:46:21 by adebray           #+#    #+#             */
/*   Updated: 2015/01/22 12:12:20 by adebray          ###   ########.fr       */
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

// static void		print_clean_hexa(char c)
// {
// 	// ft_printf("1: %d\n", c);


// 	if (c >= 0 && c < 10)
// 		ft_printf("%d", c);
// 	else if (c == 10)
// 		write(0, "a", 1);
// 	else if (c == 11)
// 		write(0, "b", 1);
// 	else if (c == 12)
// 		write(0, "c", 1);
// 	else if (c == 13)
// 		write(0, "d", 1);
// 	else if (c == 14)
// 		write(0, "e", 1);
// 	else if (c == 15)
// 		write(0, "f", 1);
// 	else
// 	{
// 		print_clean_hexa(c % 16);
// 		print_clean_hexa(c / 16);
// 	}

// 	// ft_printf("2: %d\n", c);
// 	write(0, " ", 1);
// }

static int			ft_printx(unsigned int decimal)
{
	int				cmp;

	cmp = 0;
	if (decimal == 10)
		cmp += ft_printf("%c", 'a');
	else if (decimal == 11)
		cmp += ft_printf("%c", 'b');
	else if (decimal == 12)
		cmp += ft_printf("%c", 'c');
	else if (decimal == 13)
		cmp += ft_printf("%c", 'd');
	else if (decimal == 14)
		cmp += ft_printf("%c", 'e');
	else if (decimal == 15)
		cmp += ft_printf("%c", 'f');
	return (cmp);
}

static void		print_clean_hexa(char c)
{
	int				cmp;

	cmp = 0;
	if (c < 16)
	{
		if (c >= 10)
			cmp += ft_printx(c);
		else
			cmp += ft_printf("%d", c);
	}
	else
	{
		cmp += ft_puthexa(c / 16);
		cmp += ft_printf("%x", c % 16);
	}
	ft_printf(" ");
}


static void		print_memory(t_memory *memory)
{
	int			index;

	index = 0;
	ft_printf("size: %d\n", memory->size);
	while (index < memory->size)
	{
		print_clean_hexa((unsigned char)memory->memory[index]);
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
