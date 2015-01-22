/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 04:40:40 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/22 07:00:01 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label		*get_last_label(void)
{
	t_label	*label;

	label = get_champion(0)->labels;

	while (label && label->next)
	{
		if (label->next == NULL)
			break ;

		label = label->next;
	}

	return label;
}

t_label		*add_label(char *name)
{
	t_label	*label;
	t_label	*new;

	new = malloc(sizeof(t_label));
	new->name = ft_strdup(name);
	new->next = NULL;

	label = get_last_label();

	if (label)
		label->next = new;
	else
		get_champion(0)->labels = new;

	return new;
}