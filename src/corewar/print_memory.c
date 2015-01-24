/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 23:02:45 by adebray           #+#    #+#             */
/*   Updated: 2015/01/24 01:53:54 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <corewar.h>
#include <ncurses.h>

static int			ft_printx(unsigned int decimal)
{
	int				cmp;

	cmp = 0;
	if (decimal == 10)
		cmp += wprintw(stdscr, "%c", 'a');
	else if (decimal == 11)
		cmp += wprintw(stdscr, "%c", 'b');
	else if (decimal == 12)
		cmp += wprintw(stdscr, "%c", 'c');
	else if (decimal == 13)
		cmp += wprintw(stdscr, "%c", 'd');
	else if (decimal == 14)
		cmp += wprintw(stdscr, "%c", 'e');
	else if (decimal == 15)
		cmp += wprintw(stdscr, "%c", 'f');
	return (cmp);
}

static void		print_clean_hexa(unsigned char c)
{
	if (c < 16)
	{
		if (c >= 10)
		{
			wprintw(stdscr, "0");
			ft_printx(c);
		}
		else
			wprintw(stdscr, "0%d", c);
	}
	else
		wprintw(stdscr, "%x", c);
	wprintw(stdscr, " ");
}

void		print_memory(t_memory *memory)
{
	int			index;

	index = 0;
	while (index < memory->size)
	{
		wattrset(stdscr, COLOR_PAIR(memory->memory[index].colorp));
		print_clean_hexa((unsigned char)memory->memory[index].op);
		wattroff(stdscr, COLOR_PAIR(memory->memory[index].colorp));

		if (index % (IDX_MOD / 8) == (IDX_MOD / 8) - 1)
			wprintw(stdscr, "\n");
		index += 1;
	}
}
