/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managefile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 16:57:58 by adebray           #+#    #+#             */
/*   Updated: 2015/01/21 16:45:44 by adebray          ###   ########.fr       */
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

void	filebinaryprint(t_file *head)
{
	if (head)
	{
		// ft_printf("%p\n", head);
		int i;
		i = 0;
		while (i < 80)
		{
			ft_printf(" %d", (char)head->str[i]);
			i += 1;
		}
		ft_printf("\n");
		filebinaryprint(head->next);
	}
}

t_file	*initfile(char *str)
{
	t_file	*new;

	if (!(new = (t_file*)malloc(sizeof(t_file))))
		return (NULL);
	if (!(new->str = (char*)malloc(sizeof(char) * 80)))
		return (NULL);
	ft_memcpy(new->str, str, 80);
	new->str[80] = '\0';
	new->next = NULL;
	return (new);
}

void	print_champion(t_file *head)
{
	(void)head;
}

void	*manage_file(int macro)
{
	static char		this_str[80];
	static t_file	*head;
	static t_file	*current;

	if (macro == NEW)
	{
		head = initfile(this_str);
		current = head;
		return (head);
	}
	else if (macro == GET)
		return (&head);
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
	else if (macro == PRINTBINARY)
		filebinaryprint(head);
	else if (macro == 66)
		print_champion(head);
	return (NULL);
}
