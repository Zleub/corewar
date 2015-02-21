/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/21 15:35:30 by adebray           #+#    #+#             */
/*   Updated: 2015/02/21 20:30:41 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void		live(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "live");
}
static void		ld(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "ld");
}
static void		st(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "st");
}
static void		add(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "add");
}
static void		sub(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "sub");
}
static void		and(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "and");
}
static void		or(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "or");
}
static void		xor(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "xor");
}
static void		zjmp(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "zjmp");
}
static void		ldi(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "ldi");
}

static void		sti(t_process *p)
{
	(void)p;
	int			reg_size;
	int			i;
	int			address;

	reg_size = REG_SIZE;
	address = get_int_from_index(1) + get_int_from_index(2);
	dprintf(OUT, "sti: store r%d to %d + %d: %d\n", get_int_from_index(0), get_int_from_index(1), get_int_from_index(2), address);
	// g_memory[address + p->index].op = p->registers[get_int_from_index(0)];
	i = 0;
	while (i < reg_size)
	{
		g_memory[address + p->index + i].op = p->registers[get_int_from_index(0) - 1][i];
		i += 1;
	}
}

static void		_mfork(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "_mfork");
}
static void		lld(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "lld");
}
static void		lldi(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "lldi");
}
static void		lfork(t_process *p)
{
	(void)p;
	dprintf(OUT, "instr: %s\n", "lfork");
}
static void		aff(t_process *p)
{
	(void)p;
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
