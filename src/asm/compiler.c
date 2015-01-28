/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/27 21:10:16 by nsierra-          #+#    #+#             */
/*   Updated: 2015/01/28 03:00:59 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include <fcntl.h>
#include <libft.h>
#include <stdio.h>

static int		invertoctets(int src)
{
	return ((src >> 24) & 0xff) |
		((src << 8) & 0xff0000) |
		((src >> 8) & 0xff00) |
		((src << 24) & 0xff000000);
}

static void		init_header(header_t *champ_header, const t_champion *champion)
{

}

static void		write_header(int fd, const t_champion *champion)
{
	header_t	champ_header;
	char		*tmp;

	ft_bzero(&champ_header, sizeof(header_t));
	tmp = ft_strsub(champion->name, 7, ft_strlen(champion->name) - 8);
	ft_strcat(champ_header.prog_name, tmp);
	free(tmp);
	tmp = ft_strsub(champion->comment, 10, ft_strlen(champion->comment) - 11);
	ft_strcat(champ_header.comment, tmp);
	free(tmp);
	champ_header.magic = invertoctets(COREWAR_EXEC_MAGIC);
	champ_header.prog_size = invertoctets(430);
	write(fd, &champ_header, sizeof(header_t));
}

static void		compile_commands(int fd, t_command *command)
{
	if (!command)
		return ;
	write(fd, &command->opcode, sizeof(command->opcode));
}

void			compile(const t_champion *champion)
{
	int			fd;
	int			val;

	(void)val;
	if ((fd = open("prout.txt", O_WRONLY | O_CREAT | O_TRUNC)) <= 0)
		return ;
	write_header(fd, champion);
	compile_commands(fd, champion->commands);
}
