/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 03:01:28 by nsierra-          #+#    #+#             */
/*   Updated: 2015/05/14 03:01:29 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include <stdio.h>

static int		bullshit_case(uint cmd_offset)
{
	t_command	*cursor;

	cursor = get_champion(0)->commands;
	while (cursor)
	{
		if (!cursor->next)
			return ((cursor->offset + cursor->size) - cmd_offset);
		cursor = cursor->next;
	}
	return (0);
}

static int		extract_lab2(uint cmd_offset, t_label *lab_cur, t_label *prev)
{
	t_command	*target_cmd;

	if (lab_cur->target && (target_cmd = lab_cur->target))
		return (target_cmd->offset - cmd_offset);
	else if (lab_cur == prev)
		return (bullshit_case(cmd_offset));
	else if (!lab_cur->target)
	{
		if (!lab_cur->next && (target_cmd = prev->target))
		{
			while (target_cmd->next)
				target_cmd = target_cmd->next;
			return (target_cmd->offset - cmd_offset + 3);
		}
		lab_cur = lab_cur->next;
		target_cmd = lab_cur->target;
		return (target_cmd->offset - cmd_offset);
	}
	return (0);
}

static int		extract_lab(uint cmd_offset, char *lab)
{
	t_label		*lab_cur;
	t_label		*prev;

	lab_cur = get_champion(0)->labels;
	prev = lab_cur;
	while (lab_cur)
	{
		if (!ft_strcmp(lab_cur->name, lab))
			return (extract_lab2(cmd_offset, lab_cur, prev));
		prev = lab_cur;
		lab_cur = lab_cur->next;
	}
	ft_putstr(lab);
	die(" : label not found. Abording.");
	return (0);
}

static int		extract_dir(const char *arg, uint offset)
{
	char		*lab;

	lab = ft_strchr(arg, LABEL_CHAR);

	if (ft_isdigit(arg[1]))
		return (ft_atoi(ft_strsub(arg, 1, ft_strlen(arg) - 1)));
	else
		return (extract_lab(offset, lab + 1));
}

int				get_arg(t_arg_type type, const char *arg, uint offset)
{
	if (type == REG_CODE)
		return (ft_atoi(ft_strsub(arg, 1, ft_strlen(arg) - 1)));
	else if (type == DIR_CODE)
		return (extract_dir(arg, offset));
	else if (type == IND_CODE)
		return (ft_atoi(arg));
	return (0);
}
