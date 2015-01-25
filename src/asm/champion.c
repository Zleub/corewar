/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/25 15:40:02 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/25 16:12:57 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	free_champion(t_champion *champion)
{
	t_command	*command;
	t_command	*ctmp;
	t_label		*label;
	t_label		*ltmp;

	label = champion->labels;
	while (label)
	{
		free(label->name);
		ltmp = label;
		label = label->next;
		free(ltmp);
	}
	command = champion->commands;
	while (command)
	{
		while (*command->raw_args)
			free(*(command->raw_args++));
		ctmp = command;
		command = command->next;
		free(ctmp);
	}
}

t_champion	*get_champion(int new)
{
	static t_champion	*champion;

	if (new)
	{
		free_champion(champion);
		champion = NULL;
	}
	if (champion == NULL)
	{
		champion = (t_champion*)malloc(sizeof(t_champion));
		champion->name = NULL;
		champion->comment = NULL;
		champion->commands = NULL;
		champion->labels = NULL;
	}
	return (champion);
}
