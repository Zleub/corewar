/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 23:02:45 by adebray           #+#    #+#             */
/*   Updated: 2015/01/23 23:04:55 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <corewar.h>

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

static void		print_clean_hexa(unsigned char c)
{
	int				cmp;

	cmp = 0;
	if (c < 16)
	{
		if (c >= 10)
		{
			ft_printf("0");
			cmp += ft_printx(c);
		}
		else
			cmp += ft_printf("0%d", c);
	}
	else
	{
		cmp += ft_puthexa(c / 16);
		cmp += ft_printf("%x", c % 16);
	}
	ft_printf(" ");
}

void		print_memory(t_memory *memory)
{
	int			index;

	index = 0;
	ft_printf("size: %d\n", memory->size);
	while (index < memory->size)
	{
		print_clean_hexa((unsigned char)memory->memory[index].op);
		if (index % (IDX_MOD / 8) == (IDX_MOD / 8) - 1)
			ft_printf("\n");
		index += 1;
	}
	ft_printf("\n");
}
