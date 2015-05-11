/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/21 15:35:30 by adebray           #+#    #+#             */
/*   Updated: 2015/05/09 21:35:10 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void		live(t_process *p)
{
	int		nbr;

	nbr = GET_(int)(&g_instruction[0]);
	if (g_corewar.verb > 0)
		dprintf(OUT, "\tlive for player : %d\n", nbr);
	if (nbr <= 0 || nbr > g_corewar.player_nbr)
		return ;
	p->lives += 1;
	g_corewar.scores[nbr - 1] += 1;
	g_corewar.last_alive = nbr;
}

int		max_size();

static void		ld(t_process *p)
{
	int		reg;
	t_type	u;

	u.i = 0;
	if (g_instruction[0].size == 1)
		u.c = GET_(char)(&g_instruction[0]);
	else if (g_instruction[0].size == 2)
		u.s = GET_(short)(&g_instruction[0]);
	else if (g_instruction[0].size == 4)
		u.i = GET_(int)(&g_instruction[0]);

	reg = GET_(int)(&g_instruction[1]);
	p->carry = write_registers_reverse(reg - 1, p, (char *)&(u), g_instruction[0].size);
}

static void		st(t_process *p)
{
	int		reg;
	t_type	u;

	u.i = 0;
	reg = GET_(int)(&g_instruction[0]);
	if (g_instruction[1].size == 1)
	{
		u.c = GET_(char)(&g_instruction[1]);
		write_registers(u.c - 1, p, p->registers[reg - 1], REG_SIZE);
		return ;
	}
	else if (g_instruction[1].size == 2)
		u.s = GET_(short)(&g_instruction[1]);
	else if (g_instruction[1].size == 4)
		u.i = GET_(int)(&g_instruction[1]);
	write_memory(u.i + p->index, p->registers[reg - 1], REG_SIZE);
}

static void		add(t_process *p)
{
	char	carry;
	int		reg[3];
	int		i;

	i = 0;
	carry = 0;
	reg[0] = get_int(&g_instruction[0]);
	reg[1] = get_int(&g_instruction[1]);
	reg[2] = get_int(&g_instruction[2]);
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tadd r%d + r%d -> r%d\n", reg[0], reg[1], reg[2]);

	while (i < REG_SIZE)
	{
		p->registers[reg[2] - 1][i] = p->registers[reg[0] - 1][i] + p->registers[reg[1] - 1][i];
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
	char	carry;
	int		reg[3];
	int		i;

	i = 0;
	carry = 0;
	reg[0] = get_int(&g_instruction[0]);
	reg[1] = get_int(&g_instruction[1]);
	reg[2] = get_int(&g_instruction[2]);
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tsub r%d + r%d -> r%d\n", reg[0], reg[1], reg[2]);

	while (i < REG_SIZE)
	{
		p->registers[reg[2] - 1][i] = p->registers[reg[0] - 1][i] - p->registers[reg[1] - 1][i];
		carry = carry | p->registers[reg[2] - 1][i];
		i += 1;
	}
	if (!carry)
		p->carry = 1;
	else
		p->carry = 0;
}

char			*get_reg(t_process *p, t_instruction *i)
{
	int			reg;

	reg = GET_(char)(i);
	return (p->registers[reg - 1]);
}

static void		and(t_process *p)
{
	int		i;
	int		reg;

	char *ptr1;
	short *ptr4;
	if (g_instruction[0].size == 1)
		ptr1 = get_reg(p, &g_instruction[0]);
	else if (g_instruction[0].size == 2)
		ptr4 = (short *)(&(get_int(&g_instruction[0])));
	else if (g_instruction[0].size == 4)
		ptr1 = GET_(int)(&g_instruction[0]);

	char *ptr2;
	if (g_instruction[1].size == 1)
		ptr2 = get_reg(p, &g_instruction[1]);


	// else if (g_instruction[1].size == 2)
	// 	u2.s = GET_(short)(&g_instruction[1]);
	// else if (g_instruction[1].size == 4)
	// 	u2.i = GET_(int)(&g_instruction[1]);

	// reg = GET_(int)(&g_instruction[2]);
	// i = 0;
	// while (i < g_instruction[0].size && i < g_instruction[1].size)
	// {
	// 	p->registers[reg - 1][i] = (char*)(&(u1))[i] & (char*)(&(u2))[i];
	// 	carry = carry | p->registers[reg[2] - 1][i];
	// 	i += 1;
	// }
	// if (!carry)
	// 	p->carry = 1;
	// else
	// 	p->carry = 0;
}

static void		or(t_process *p)
{
	char	carry;
	int		reg[3];
	int		i;

	i = 0;
	carry = 0;
	reg[0] = get_int(&g_instruction[0]);
	reg[1] = get_int(&g_instruction[1]);
	reg[2] = get_int(&g_instruction[2]);
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
	reg[0] = get_int(&g_instruction[0]);
	reg[1] = get_int(&g_instruction[1]);
	reg[2] = get_int(&g_instruction[2]);
	if (g_corewar.verb > 1)
		dprintf(OUT, "\txor r%d + r%d -> r%d\n", reg[0], reg[1], reg[2]);

	while (i < REG_SIZE)
	{
		p->registers[reg[2] - 1][i] = p->registers[reg[0] - 1][i] ^ p->registers[reg[1] - 1][i];
		carry = carry | p->registers[reg[2] - 1][i];
		i += 1;
	}
	if (!carry)
		p->carry = 1;
	else
		p->carry = 0;
}

static void		zjmp(t_process *p)
{
	(void)p;
	short	dest;

	dest = get_int(&g_instruction[0]);
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tzjmp: %d @ %d -> ", p->number, dest);
	if (p->carry == 1)
	{
		if (g_corewar.verb > 1)
			dprintf(OUT, "SUCCESS\n");
		p->index += dest - 3;
		if (g_corewar.verb > 1)
			dprintf(OUT, "new index: %d\n", p->index);
	}
	else
	{
		if (g_corewar.verb > 1)
			dprintf(OUT, "FAILED\n");
	}
}

static void		ldi(t_process *p)
{
	(void)p;
	if (g_corewar.verb > 1)
		dprintf(OUT, "instr: %s\n", "ldi");
	print_instruction();
	// int i;
	// short s;

	// if (g_instruction[0].type == T_REG && g_instruction[1].type == T_REG)
}

static void		sti(t_process *p)
{
	int			i;
	int			address;

	address = (get_int(&g_instruction[1]) + get_int(&g_instruction[2]));
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tsti: store r%d to %d + %d: %d (%d)\n",
			get_int(&g_instruction[0]), get_int(&g_instruction[1]), get_int(&g_instruction[2]), address, address % IDX_MOD + p->index);
	i = 0;
	while (i < REG_SIZE)
	{
		g_memory[address % IDX_MOD + p->index + i].op = p->registers[get_int(&g_instruction[0]) - 1][i];
		i += 1;
	}
}

static void		_mfork(t_process *p)
{
	t_process	*new;
	short		dest;

	dest = get_int(&g_instruction[0]);
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tfork: %d @ %d (%d)\n", p->number, dest, p->index + dest % IDX_MOD);
	new = new_process(p);
	add_process(new);
	new->index = p->index + dest % IDX_MOD;
	new->delay = get_op(new).cycles;
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
