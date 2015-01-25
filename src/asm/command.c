/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 04:40:40 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/25 16:13:44 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_command		*get_last_command(void)
{
	t_command	*command;

	command = get_champion(0)->commands;
	while (command && command->next)
	{
		if (command->next == NULL)
			break ;
		command = command->next;
	}
	return (command);
}

t_command		*add_command(t_command *new)
{
	t_command	*command;

	command = get_last_command();
	if (command)
		command->next = new;
	else
		get_champion(0)->commands = new;
	return (new);
}
