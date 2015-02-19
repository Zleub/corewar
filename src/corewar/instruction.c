/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 21:46:58 by adebray           #+#    #+#             */
/*   Updated: 2015/02/19 13:38:09 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		init_instruction(int max_size)
{
	int		i = 0;

	dprintf(OUT, "%d\n", max_size);
	while (i < MAX_ARGS_NUMBER)
	{
		if (!(g_instruction[i].args = (char *)malloc(sizeof(char) * max_size)))
			die(-1);
		i += 1;
	}
}

int			get_codingoctet(int index)
{
	int			coding_octet;

	coding_octet = (int)g_memory[index + 1].op;
	// dprintf(1, "coding_octet: %d\n", coding_octet);
	return (coding_octet);
}

int			get_size(int macro, int magic)
{
	if (macro == REG_CODE)
	{
		return (1);
	}
	else if (macro == DIR_CODE)
	{
		if (magic == 1)
			return (DIR_SIZE / 2);
		else
			return (DIR_SIZE);
	}
	else if (macro == IND_CODE)
	{
		return (IND_SIZE);
	}
	return (0);
}

char		*get_string_for_memory(int size, int offset)
{
	int		i;
	char	*tmp;

	tmp = ft_memalloc(size);
	i = 0;
	while (i < size)
	{
		tmp[i] = g_memory[offset + i].op;
		i += 1;
	}
	return (tmp);
}

int			get_multisize(t_process *p, t_op *op)
{
	int				tmpsize;
	int				size;
	int				i;
	int				count;
	unsigned char	coding_octet;

	size = 0;
	coding_octet = get_codingoctet(p->index);
	count = 0;
	while (count < op->arg_number)
	{
		i = 0;
		i = coding_octet >> 6;
		if (i == REG_CODE || i == DIR_CODE || i == IND_CODE)
		{
			tmpsize = get_size(i, op->unknown1);
			g_instruction[count].type = i;
			g_instruction[count].args = get_string_for_memory(tmpsize, p->index + 2 + size);
			g_instruction[count].size = tmpsize;
			coding_octet = coding_octet << 2;
			size += tmpsize;
		}
		count += 1;
	}
	return (size);
}

void		reset_instruction()
{
	int		i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		g_instruction[i].type = 0;
		g_instruction[i].size = 0;
		if (g_instruction[i].args)
		{
			free(g_instruction[i].args);
			g_instruction[i].args = NULL;
		}
		i += 1;
	}
}

int			fill_instruction(t_process *p)
{
	t_op	op;
	int		size;

	size = 1;
	op = get_op(p);
	reset_instruction();
	if (op.coding_octet == 0)
	{
		size += get_size(op.args[0], op.unknown1);
		g_instruction[0].args = get_string_for_memory(size - 1, p->index + 1);
		g_instruction[0].type = op.args[0];
		g_instruction[0].size = size - 1;
	}
	else
	{
		size += 1;
		size += get_multisize(p, &op);
	}
	return (size);
}

void		print_instruction()
{
	int		i = 0;

	while (i < MAX_ARGS_NUMBER)
	{
		int j = 0;
		dprintf(OUT, "[%d]: ", i);
		while (j < g_instruction[i].size)
		{
			print_clean_hexa(g_instruction[i].args[j]);
			dprintf(OUT, " ");
			j += 1;
		}
		dprintf(OUT, "\n");
		i += 1;
	}
}

void		print_instruction_decimal()
{
	int		i = 0;

	while (i < MAX_ARGS_NUMBER)
	{
		int j = 0;
		if (g_instruction[i].type == REG_CODE)
			dprintf(OUT, "r%x", g_instruction[i].args[0]);
		else
		{
			while (j < g_instruction[i].size)
			{
				print_clean_hexa(g_instruction[i].args[j]);
				j += 1;
			}
		}
		i += 1;
		if (i < MAX_ARGS_NUMBER && g_instruction[i].args)
			dprintf(OUT, ", ");
	}
	dprintf(OUT, "\n");
}

t_op		get_op(t_process *p)
{
	extern t_op		g_op_tab[17];
	int				op_index;

	op_index = (int)g_memory[p->index].op;
	if (op_index > 15 || op_index < 0)
	{
		dprintf(1, "error op_index: %d\n", op_index);
		exit(0);
	}
	return (g_op_tab[op_index - 1]);
}

void		print_op(t_op op)
{
	dprintf(OUT, "%d: %s\n", op.arg_number, op.name);
}