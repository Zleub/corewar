/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 13:23:17 by adebray           #+#    #+#             */
/*   Updated: 2015/05/15 23:44:56 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <limits.h>

void		write_heros(int offset, t_heros *heros)
{
	unsigned int	m;
	t_process		*p;

	m = 0;
	while (m < heros->head.prog_size)
	{
		if (m >= CHAMP_MAX_SIZE)
		{
			dprintf(2, "Champ too large, plz, check with your compiler\n");
			exit(EXIT_FAILURE);
		}
		g_memory[offset + m].c = heros->color;
		g_memory[offset + m].op = (unsigned char)heros->content[m];
		m += 1;
	}
	g_memory[offset].p = 1;

	p = new_process(NULL);
	p->index = offset;
	p->delay = get_op(p)->cycles;

	// WHAT IF REG_SIZE > 4
	p->registers[0][REG_SIZE - 4] = 0;
	p->registers[0][REG_SIZE - 3] = 0;
	p->registers[0][REG_SIZE - 2] = 0;
	p->registers[0][REG_SIZE - 1] = heros->number;
	p->p_number = heros->number;
	p->lives = 0;
	add_process(p);

	g_memory[p->index].p = 1;
	// init_pair(heros->color, ft_hashich(heros->head.prog_name), COLOR_BLACK);
}

void		init_memory(int player_nbr)
{
	int		i;
	int		offset;

	ft_bzero(g_memory, sizeof(t_cell) * MEM_SIZE);
	i = 0;
	offset = MEM_SIZE / player_nbr;
	while (i < player_nbr)
	{
		// ft_printf("Introducing %s, n: %d, %db of code\n", g_heros[i].head.prog_name, g_heros[i].number, g_heros[i].head.prog_size * 8);
		ft_printf("Introducing %s, n: %d, %db of code", g_heros[i].head.prog_name, g_heros[i].number, g_heros[i].head.prog_size * 8);
		ft_printf("\t\"%s\"\n", g_heros[i].head.comment);
		write_heros(i * offset, &g_heros[i]);
		i += 1;
	}
}

static void			ft_printx(unsigned int decimal)
{
	if (decimal == 10)
		ft_putchar_fd('a', OUT);
	else if (decimal == 11)
		ft_putchar_fd('b', OUT);
	else if (decimal == 12)
		ft_putchar_fd('c', OUT);
	else if (decimal == 13)
		ft_putchar_fd('d', OUT);
	else if (decimal == 14)
		ft_putchar_fd('e', OUT);
	else if (decimal == 15)
		ft_putchar_fd('f', OUT);
}

void		print_clean_hexa(unsigned char c)
{
	if (c < 16)
	{
		if (c >= 10)
		{
			ft_putchar_fd('0', OUT);
			ft_printx(c);
		}
		else
		{
			ft_putchar_fd('0', OUT);
			ft_putchar_fd(c + 48, OUT);
		}
	}
	else
		dprintf(OUT, "%x", c);
}

void		dump_memory(void)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		print_clean_hexa(g_memory[i].op);
		ft_putchar_fd(' ', OUT);
		if (i % (IDX_MOD / 8) == (IDX_MOD / 8) - 1)
			ft_putchar_fd('\n', OUT);
		i += 1;
	}
}

int			write_memory(int index, t_process *p, char *str, int len)
{
	char	carry;
	int		address;
	int		offset;
	int		i;


	i = 0;
	carry = 0;
	offset = max_size() - len;
	dprintf(OUT, "index: %d, p->index: %d\n", index, p->index);
	while (i < len)
	{
		if (p->index + index < 0)
			address = (p->index + p->index + index + i);
		else
			address = (p->index + index + i) % MEM_SIZE;

		if (address < 0)
			address = MEM_SIZE - address;

		dprintf(OUT, "write_memory @ %d\n", address % MEM_SIZE);
		g_memory[address % MEM_SIZE].op = str[i + offset];
		carry = carry | g_memory[address ].op;
		i += 1;
	}
	if (!carry)
		return (1);
	else
		return (0);
}

void		cpy_memory(t_process *p, t_instruction *inst, char str[DIR_SIZE])
{
	int		i;
	int		address;
	short	ind;

	ind = GET_(short)(inst);
	i = 0;
	while (i < DIR_SIZE)
	{
		address = (p->index + ind + i) % IDX_MOD;
		str[i] = g_memory[address].op;
		i += 1;
	}
}
