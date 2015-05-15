/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/21 15:35:30 by adebray           #+#    #+#             */
/*   Updated: 2015/05/15 18:00:15 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void		live(t_process *p)
{
	int		nbr;

	nbr = GET_(int)(&g_instruction[0]);
	if (g_corewar.verb > 0)
		dprintf(OUT, "%d\n", nbr);
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

	reg = GET_(int)(&g_instruction[1]);
	if (g_corewar.verb > 1)
		dprintf(OUT, "%d, r%d \n", GET_(int)(&g_instruction[0]), GET_(int)(&g_instruction[1]));
	p->carry = write_registers(reg - 1, p, g_array[0], DIR_SIZE);
}

static void		st(t_process *p)
{
	int			reg;

	if (g_corewar.verb > 1)
		dprintf(OUT, "r%d %d\n", GET_(short)(&g_instruction[0]), GET_(short)(&g_instruction[1]));
	if (g_instruction[1].type == IND_CODE)
		p->carry = write_memory(GET_(short)(&g_instruction[1]) % IDX_MOD, p, g_array[0], DIR_SIZE);
	else if (g_instruction[1].type == REG_CODE)
	{
		reg = GET_(int)(&g_instruction[1]);
		p->carry = write_registers(reg - 1, p, g_array[0], REG_SIZE);
	}
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

static void		and(t_process *p)
{
	char	tmp[REG_SIZE];
	int		reg;
	int		i;

	if (g_corewar.verb > 1)
		dprintf(OUT, "\tand\n");

	reg = GET_(int)(&g_instruction[2]);
	i = 0;
	while (i < REG_SIZE)
	{
		tmp[i] = g_array[0][i] & g_array[1][i];
		i += 1;
	}
	p->carry = write_registers(reg - 1, p, tmp, REG_SIZE);
}

static void		or(t_process *p)
{
	char	tmp[REG_SIZE];
	int		reg;
	int		i;

	if (g_corewar.verb > 1)
		dprintf(OUT, "\tor\n");

	reg = GET_(int)(&g_instruction[2]);
	i = 0;
	while (i < REG_SIZE)
	{
		tmp[i] = g_array[0][i] | g_array[1][i];
		i += 1;
	}
	p->carry = write_registers(reg - 1, p, tmp, REG_SIZE);
}

static void		xor(t_process *p)
{
	char	tmp[REG_SIZE];
	int		reg;
	int		i;

	if (g_corewar.verb > 1)
		dprintf(OUT, "\txor\n");

	reg = GET_(int)(&g_instruction[2]);
	i = 0;
	while (i < REG_SIZE)
	{
		tmp[i] = g_array[0][i] ^ g_array[1][i];
		i += 1;
	}
	p->carry = write_registers(reg - 1, p, tmp, REG_SIZE);
}

static void		zjmp(t_process *p)
{
	short	dest;

	dest = get_int(&g_instruction[0]);
	if (g_corewar.verb > 1)
		dprintf(OUT, "@ %d -> ", dest);
	if (p->carry == 1)
	{
		if (g_corewar.verb > 1)
			dprintf(OUT, "SUCCESS\n");
		p->index += dest - 3;
		// if (g_corewar.verb > 1)
		// 	dprintf(OUT, "new index: %d\n", p->index);
	}
	else
	{
		if (g_corewar.verb > 1)
			dprintf(OUT, "FAILED\n");
	}
}

static void		ldi(t_process *p)
{
	char	tmp[REG_SIZE];
	int		ind;
	int		reg;
	int		i;
	int		address;

	if (g_corewar.verb > 1)
		dprintf(OUT, "\tldi\n");

	i = 0;
	while (i < DIR_SIZE / 2)
	{
		((char *)&ind)[DIR_SIZE / 2 - 1 - i] = g_array[0][i] + g_array[1][i];
		i += 1;
	}
	i = 0;
	while (i < REG_SIZE)
	{
		address = (p->index + ind + i) % IDX_MOD;
		dprintf(OUT, "AIDJWOI  %d\n", address);
		tmp[i] = g_memory[address].op;
		i += 1;
	}
	reg = GET_(int)(&g_instruction[2]);
	write_registers(reg - 1, p, tmp, REG_SIZE);
}

static void		sti(t_process *p)
{
	int		ind;
	int		reg;
	int		i;

	i = 0;
	while (i < DIR_SIZE)
	{
		((char *)&ind)[DIR_SIZE - 1 - i] = g_array[1][i] + g_array[2][i];
		i += 1;
	}
	reg = GET_(int)(&g_instruction[0]);
	if (g_corewar.verb > 1)
		dprintf(OUT, "r%d, %d + %d\n", GET_(int)(&g_instruction[0]), GET_(int)(&g_instruction[1]), GET_(int)(&g_instruction[2]));
	write_memory(ind % IDX_MOD, p, p->registers[reg - 1], DIR_SIZE);
}

static void		_mfork(t_process *p)
{
	t_process	*new;
	short		dest;

	dest = get_int(&g_instruction[0]);
	if (g_corewar.verb > 1)
		dprintf(OUT, "%d @ %d (%d)\n", p->number, dest, p->index + dest % IDX_MOD);
	new = new_process(p);
	add_process(new);
	new->index = p->index + dest % IDX_MOD;
	new->delay = get_op(new)->cycles;
}

static void		lld(t_process *p)
{
	char	tmp[DIR_SIZE];
	int		reg;
	int		address;
	int		i;

	if (g_corewar.verb > 1)
		dprintf(OUT, "\tlld\n");
	reg = GET_(int)(&g_instruction[1]);
	if (g_instruction[0].type == DIR_CODE)
		p->carry = write_registers(reg - 1, p, g_array[0], DIR_SIZE);
	else if (g_instruction[0].type == IND_CODE)
	{
		i = 0;
		while (i < DIR_SIZE)
		{
			address = (p->index + GET_(short)(&g_instruction[0])) % MEM_SIZE;
			tmp[i] = g_memory[address].op;
			i += 1;
		}
		p->carry = write_registers(reg - 1, p, tmp, REG_SIZE);
	}
}

static void		lldi(t_process *p)
{
	char	dir_tmp[DIR_SIZE];
	char	reg_tmp[REG_SIZE];
	int		address;
	int		i;
	int		ind;
	int		reg;

	if (g_corewar.verb > 1)
		dprintf(OUT, "\tlldi\n");

	reg = GET_(int)(&g_instruction[2]);
	if (g_instruction[0].type == IND_CODE)
	{
		i = 0;
		while (i < DIR_SIZE)
		{
			address = (p->index + GET_(short)(&g_instruction[0])) % MEM_SIZE;
			dir_tmp[i] = g_memory[p->index + GET_(short)(&g_instruction[0])].op;
			i += 1;
		}
		i = 0;
		while (i < DIR_SIZE)
		{
			((char *)&ind)[DIR_SIZE - 1 - i] = dir_tmp[i] + g_array[1][i];
			i += 1;
		}
		i = 0;
		while (i < REG_SIZE)
		{
			address = (p->index + ind + i) % MEM_SIZE;
			// if (address >= 0 || address < MEM_SIZE)
				reg_tmp[i] = g_memory[address].op;
			// else
			// 	reg_tmp[i] = 0;
			i += 1;
		}
		p->carry = write_registers(reg - 1, p, reg_tmp, REG_SIZE);
	}
	else
	{
		i = 0;
		while (i < DIR_SIZE)
		{
			((char *)&ind)[DIR_SIZE - 1 - i] = g_array[0][i] + g_array[1][i];
			i += 1;
		}
		i = 0;
		while (i < REG_SIZE)
		{
			address = (p->index + (short)ind + i);
			// dprintf(OUT, "++ %d ++", address) % MEM_SIZE;
			// if (address >= 0 || address < MEM_SIZE)
				reg_tmp[i] = g_memory[address].op;
			// else
			// 	reg_tmp[i] = 0;
			// dprintf(OUT, "-- %d --", reg_tmp[i]);
			i += 1;
		}
		p->carry = write_registers(reg - 1, p, reg_tmp, REG_SIZE);
	}
}

static void		lfork(t_process *p)
{
	t_process	*new;
	short		dest;

	dest = get_int(&g_instruction[0]);
	if (g_corewar.verb > 1)
		dprintf(OUT, "\tlfork: %d @ %d (%d)\n", p->number, dest, p->index + dest % MEM_SIZE);
	new = new_process(p);
	add_process(new);
	new->index = p->index + dest % MEM_SIZE;
	new->delay = get_op(new)->cycles;
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
