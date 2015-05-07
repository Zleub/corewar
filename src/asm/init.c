/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 01:54:46 by amaurer           #+#    #+#             */
/*   Updated: 2015/05/01 19:03:00 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <libft.h>
#include <fcntl.h>
#include <stdio.h>

void	usage(void)
{
	ft_putendl("Usage: ./asm filename");
	exit(EXIT_SUCCESS);
}

int		open_file(char const *pathname)
{
	int	fd;

	fd = open(pathname, O_RDONLY);
	if (fd == -1)
		die("Please enter a correct file.");
	return (fd);
}

static void	print_champion(t_champion *c)
{
	t_command	*command;
	uint		i;

	printf("\nName: %s\n", c->name);
	printf("Comment: %s\n\n", c->comment);
	printf("Commandes:\n");

	command = c->commands;
	while (command)
	{
		printf("   %s (args: %u, size: %u, offset: %u)\n", command->op->name, command->op->arg_number, command->size, command->offset);

		i = 0;
		while (command->raw_args[i])
		{
			printf("      %s\n", command->raw_args[i]);
			i++;
		}
		printf("\n");
		command = command->next;
	}
}

void	init(int argc, char const **argv)
{
	int	fd;

	if (argc != 2)
		usage();
	fd = open_file(argv[1]);
	parse_file(fd);
	print_champion(get_champion(0));
	compile(argv[1]);
	close(fd);
}
