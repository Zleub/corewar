/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 01:54:46 by amaurer           #+#    #+#             */
/*   Updated: 2015/01/25 16:14:47 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <libft.h>
#include <fcntl.h>

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

void	init(int argc, char const **argv)
{
	int	fd;

	if (argc != 2)
		usage();
	fd = open_file(argv[1]);
	parse_file(fd);
	close(fd);
}
