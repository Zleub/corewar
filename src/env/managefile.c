/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managefile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 16:57:58 by adebray           #+#    #+#             */
/*   Updated: 2015/01/20 04:16:58 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

void	fileprint(t_file *head)
{
	if (head)
	{
		ft_printf("%p\n", head);
		ft_printf("%s\n", head->str);
		ft_printf("%p\n", head->next);
		fileprint(head->next);
	}
}

t_file	*initfile(char *str)
{
	t_file	*new;

	if (!(new = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

void	*manage_file(int macro)
{
	static char		*this_str;
	static t_file	*head;
	static t_file	*current;

	if (macro == NEW)
	{
		head = initfile(this_str);
		current = head;
		return (head);
	}
	else if (macro == GET)
		return (head);
	else if (macro == SET)
		return (&this_str);
	else if (macro == ADD)
	{
		if (!head)
			return (manage_file(NEW));
		if (!(current->next = initfile(this_str)))
			return (NULL);
		current = current->next;
	}
	else if (macro == PRINT)
		fileprint(head);
	return (NULL);
}
