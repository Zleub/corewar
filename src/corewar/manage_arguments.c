/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 17:01:18 by adebray           #+#    #+#             */
/*   Updated: 2015/02/15 18:36:13 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void			manage_arguments_print(char **args)
{
	int			i;

	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		dprintf(1, "%s\n", args[i]);
		i += 1;
	}
}

void			manage_arguments_fill(int count, int tmpsize, int index)
{
	t_memory	*memory;

	memory = manage_memory(GET);
	((t_arguments*)manage_arguments(GET))[count] = (int)memory->memory[index + 1].op;
}

void			manage_arguments_getcodingoctet(int index)
{
	int			coding_octet;
	t_memory	*memory;

	memory = manage_memory(GET);
	coding_octet = (int)memory->memory[index + 1].op;
	dprintf(1, "coding_octet: %d\n", coding_octet);
	return (coding_octet);
}

void			manage_arguments_getspesize(int simple, int magic)
{
	if (simple == REG_CODE)
		((t_arguments *)manage_arguments(ENV))->size += (REG_ENCODING_SIZE);
	else if (simple == DIR_CODE)
	{
		if (magic == 1)
			((t_arguments *)manage_arguments(ENV))->size += (DIR_ENCODING_SIZE / 2);
		else
			((t_arguments *)manage_arguments(ENV))->size += (DIR_ENCODING_SIZE);
	}
	else if (simple == IND_CODE)
		((t_arguments *)manage_arguments(ENV))->size += (IND_ENCODING_SIZE);
	else
		((t_arguments *)manage_arguments(ENV))->size += (DIR_ENCODING_SIZE);
}

void			manage_arguments_getmultisize(unsigned char coding_octet, int magic, int index)
{
	int size = 0;
	int tmpsize = 0;
	int i = 1;
	int count = 0;

	while (count < MAX_ARGS_NUMBER)
	{
		i = 0;
		i = coding_octet >> 6;
		if (i != 0)
		{
			dprintf(1, "%d -> ", size);
			tmpsize = get_spesize(i, magic);
			size += tmpsize;
			dprintf(1, " -> %d\n", size);
			manage_arguments_fill(count, tmpsize, index);
			coding_octet = coding_octet << 2;
		}
		count += 1;
	}
	return (size);
}

void			manage_arguments_getsize(t_arguments *env, char **current)
{
	if (env->coding_octet == 0)
	{
		manage_arguments_getspesize(env->type, env->magic);
		manage_arguments_fill(0, env->size - 1, env->index);
	}
	else
	{
		env->size += 1;
		manage_arguments_getmultisize(manage_arguments_getcodingoctet(env->index), env->magic, index);
	}
}

void			*manage_arguments(int macro)
{
	static t_arguments	env;
	static char			*current[MAX_ARGS_NUMBER];

	// if (macro == INIT)
		// manage_arguments_init(&current);
	if (macro == GET)
		return (current);
	else if (macro == ENV)
		return (&env);
	else if (macro == FILL)
		manage_arguments_getsize(&env, current);
	else if (macro == PRINT)
		manage_arguments_print(current);
	else
		ft_printf("Useless calll to manage_arguments\n");
	return (NULL);
}
