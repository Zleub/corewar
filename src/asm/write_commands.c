/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 03:01:22 by nsierra-          #+#    #+#             */
/*   Updated: 2015/05/14 03:01:23 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		write_coding_octet(int fd, t_command *command)
{
	if (command->op->coding_octet)
		write(fd, &command->coding_octet, sizeof(char));
}

static void		write_opcode(int fd, t_command *command)
{
	write(fd, &command->op->opcode, sizeof(char));
}

uint			write_commands(int fd, t_champion *champion)
{
	t_command	*command;
	uint		ret;

	command = champion->commands;
	ret = 0;
	while (command)
	{
		write_opcode(fd, command);
		write_coding_octet(fd, command);
		write_parameters(fd, command);
		if (!command->next)
			ret = command->offset + command->size;
		command = command->next;
	}
	return (ret);
}
