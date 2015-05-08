/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/21 15:35:30 by adebray           #+#    #+#             */
/*   Updated: 2015/05/08 04:30:08 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void		live(t_process *p)
{
	int		nbr;

	nbr = get_int_from_index(0);
	if (g_corewar.verb > 0)
		dprintf(OUT, "\tlive: live from %d for player : %d\n", p->number, nbr);
	if (nbr < 0 || nbr > g_corewar.player_nbr)
		return ;
	p->lives += 1;
	g_corewar.scores[nbr - 1] += 1;
	g_corewar.last_alive = nbr;
}

int		max_size();

static void		ld(t_process *p)
{
	char	carry;
	int		value;
	int		reg;

	carry = 0;
	value = get_int_from_index(0);
	reg = get_int_from_index(1);
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tld: load %d -> r%d\n", value, reg);

	int i = 0;
	while (i < g_instruction[0].size)
	{
		p->registers[reg - 1][i] = g_instruction[0].args[i];
		carry = carry | g_instruction[0].args[i];
		i += 1;
	}
	if (!carry)
		p->carry = 1;
	else
		p->carry = 0;
}

static void		st(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "st");
}

static void		add(t_process *p)
{
	char	carry;
	int		reg[3];
	int		i;

	i = 0;
	carry = 0;
	reg[0] = get_int_from_index(0);
	reg[1] = get_int_from_index(1);
	reg[2] = get_int_from_index(2);
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tadd r%d + r%d -> r%d\n", reg[0], reg[1], reg[2]);

	while (i < REG_SIZE)
	{
		p->registers[reg[2] - 1][i] = p->registers[reg[0] - 1][i] | p->registers[reg[1] - 1][i];
		carry = carry | p->registers[reg[2] - 1][i];
		i += 1;
	}
	if (!carry)
		p->carry = 1;
	else
		p->carry = 0;
}

static void		sub(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "sub");
}

static void		and(t_process *p)
{
	char	carry;
	int		reg[3];
	int		i;

	i = 0;
	carry = 0;
	reg[0] = get_int_from_index(0);
	reg[1] = get_int_from_index(1);
	reg[2] = get_int_from_index(2);
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tand r%d + r%d -> r%d\n", reg[0], reg[1], reg[2]);

	while (i < REG_SIZE)
	{
		p->registers[reg[2] - 1][i] = p->registers[reg[0] - 1][i] & p->registers[reg[1] - 1][i];
		carry = carry | p->registers[reg[2] - 1][i];
		i += 1;
	}
	if (!carry)
		p->carry = 1;
	else
		p->carry = 0;
}

static void		or(t_process *p)
{
	char	carry;
	int		reg[3];
	int		i;

	i = 0;
	carry = 0;
	reg[0] = get_int_from_index(0);
	reg[1] = get_int_from_index(1);
	reg[2] = get_int_from_index(2);
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tor r%d + r%d -> r%d\n", reg[0], reg[1], reg[2]);

	while (i < REG_SIZE)
	{
		p->registers[reg[2] - 1][i] = p->registers[reg[0] - 1][i] | p->registers[reg[1] - 1][i];
		carry = carry | p->registers[reg[2] - 1][i];
		i += 1;
	}
	if (!carry)
		p->carry = 1;
	else
		p->carry = 0;
}

static void		xor(t_process *p)
{
	char	carry;
	int		reg[3];
	int		i;

	i = 0;
	carry = 0;
	reg[0] = get_int_from_index(0);
	reg[1] = get_int_from_index(1);
	reg[2] = get_int_from_index(2);
	if (g_corewar.verb > 1)
		dprintf(OUT, "\txor r%d + r%d -> r%d\n", reg[0], reg[1], reg[2]);

	while (i < REG_SIZE)
	{
		p->registers[reg[2] - 1][i] = p->registers[reg[0] - 1][i] ^ p->registers[reg[1] - 1][i];
		carry = carry | p->registers[reg[2] - 1][i];
		i += 1;
	}
	dprintf(OUT, "xor carry : %d\n", carry);
	if (!carry)
		p->carry = 1;
	else
		p->carry = 0;
}

static void		zjmp(t_process *p)
{
	(void)p;
	int	dest;

	dest = get_int_from_index(0);
	if (g_corewar.verb > 1)
		dprintf(OUT, "--------     \tzjmp: %d @ %d -> ", p->number, (signed short)dest);
	if (p->carry == 1)
	{
		dprintf(OUT, "SUCCESS\n");
		p->index = dest;
	}
	else
		dprintf(OUT, "FAILED\n");
}

static void		ldi(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "ldi");
}

static void		sti(t_process *p)
{
	int			i;
	int			address;

	print_instruction();
	address = (get_int_from_index(1) + get_int_from_index(2));
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tsti: store r%d to %d + %d: %d (%d)\n",
			get_int_from_index(0), get_int_from_index(1), get_int_from_index(2), address, address % IDX_MOD + p->index);
	// g_memory[address + p->index].op = p->registers[get_int_from_index(0)];
	i = 0;
	while (i < REG_SIZE)
	{
		g_memory[address % IDX_MOD + p->index + i].op = p->registers[get_int_from_index(0) - 1][i];
		i += 1;
	}
}

static void		_mfork(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "_mfork");
}

static void		lld(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "lld");
}

static void		lldi(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "lldi");
}

static void		lfork(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "lfork");
}

static void		aff(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "aff");
}

void (*t[16])(t_process *) = {
	live,
	ld,
	st,
	add,
	sub,
	and,
	or,
	xor,
	zjmp,
	ldi,
	sti,
	_mfork,
	lld,
	lldi,
	lfork,
	aff
};
