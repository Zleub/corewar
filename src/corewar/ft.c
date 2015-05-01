/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/21 15:35:30 by adebray           #+#    #+#             */
/*   Updated: 2015/05/01 01:37:47 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void		live(t_process *p)
{
	int		nbr;

	nbr = get_int_from_index(0);
	if (g_corewar.verb > 0)
		dprintf(OUT, "\tlive: live from %d for player : %d\n", p->number, nbr);
	p->lives += 1;
	g_corewar.scores[nbr] += 1;
}

int		max_size();

static void		ld(t_process *p)
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
}

static void		st(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "st");
}

static void		add(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "add");
}

static void		sub(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "sub");
}

static void		and(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "and");
}

static void		or(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "or");
}

static void		xor(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "xor");
}

static void		zjmp(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "zjmp");
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

	address = (get_int_from_index(1) + get_int_from_index(2));
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tsti: store r%d to %d + %d: %d (%d)\n", get_int_from_index(0), get_int_from_index(1), get_int_from_index(2), address % IDX_MOD, address);
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
