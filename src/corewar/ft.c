/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/21 15:35:30 by adebray           #+#    #+#             */
/*   Updated: 2015/05/07 15:38:41 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static int		live(t_process *p)
{
	int		nbr;

	nbr = get_int_from_index(0);
	if (g_corewar.verb > 0)
		dprintf(OUT, "\tlive: live from %d for player : %d\n", p->number, nbr);
	p->lives += 1;
	g_corewar.scores[nbr - 1] += 1;
	g_corewar.last_alive = nbr;
	return (1);
}

int		max_size();

static int		ld(t_process *p)
{
	int		value;
	int		reg;

	value = get_int_from_index(0);
	reg = get_int_from_index(1);
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tld: load %d -> r%d\n", value, reg);

	int i = 0;
	while (i < g_instruction[0].size)
	{
		p->registers[reg - 1][i] = g_instruction[0].args[i];
		i += 1;
	}
	(void)p;
	return (1);
}

static int		st(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "st");
	return (1);
}

void print_registers(t_process *p);

static int		add(t_process *p)
{
	char	carry;
	int		reg[3];
	int		i;

	i = 0;
	carry = 0;
	reg[0] = get_int_from_index(0);
	reg[1] = get_int_from_index(1);
	reg[2] = get_int_from_index(2);
	while (i < REG_SIZE)
	{
		p->registers[reg[2] - 1][i] = p->registers[reg[0] - 1][i] | p->registers[reg[1] - 1][i];
		carry = carry & p->registers[reg[2] - 1][i];
		i += 1;
	}
	if (!carry)
		return (carry);
	return (1);
}

static int		sub(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "sub");
	return (1);
}

static int		and(t_process *p)
{
	char	carry;
	int		reg[3];
	int		i;

	i = 0;
	carry = 0;
	reg[0] = get_int_from_index(0);
	reg[1] = get_int_from_index(1);
	reg[2] = get_int_from_index(2);
	while (i < REG_SIZE)
	{
		p->registers[reg[2] - 1][i] = p->registers[reg[0] - 1][i] & p->registers[reg[1] - 1][i];
		carry = carry & p->registers[reg[2] - 1][i];
		i += 1;
	}
	if (!carry)
		return (carry);
	return (1);
}

static int		or(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "or");
	return (1);
}

static int		xor(t_process *p)
{
	char	carry;
	int		reg[3];
	int		i;

	i = 0;
	carry = 0;
	reg[0] = get_int_from_index(0);
	reg[1] = get_int_from_index(1);
	reg[2] = get_int_from_index(2);
	while (i < REG_SIZE)
	{
		p->registers[reg[2] - 1][i] = p->registers[reg[0] - 1][i] ^ p->registers[reg[1] - 1][i];
		carry = carry & p->registers[reg[2] - 1][i];
		i += 1;
	}
	if (!carry)
		return (carry);
	return (1);
}

static int		zjmp(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "zjmp");
	return (1);
}

static int		ldi(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "ldi");
	return (1);
}

static int		sti(t_process *p)
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
	return (1);
}

static int		_mfork(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "_mfork");
	return (1);
}

static int		lld(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "lld");
	return (1);
}

static int		lldi(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "lldi");
	return (1);
}

static int		lfork(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "lfork");
	return (1);
}

static int		aff(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "aff");
	return (1);
}

int (*t[16])(t_process *) = {
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
