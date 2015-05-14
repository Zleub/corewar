/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 02:43:57 by nsierra-          #+#    #+#             */
/*   Updated: 2015/05/14 02:43:58 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>

static int		invertoctets(int src)
{
	char		*bytes;
	char		c;
	int			ret;

	bytes = (char *)&src;
	c = bytes[3];
	bytes[3] = bytes[0];
	bytes[0] = c;
	c = bytes[1];
	bytes[1] = bytes[2];
	bytes[2] = c;
	ft_memcpy(&ret, bytes, sizeof(int));
	return (ret);
}

static char		*determine_new_filename(const char *original_filename)
{
	char		*original_filename_dup;
	char		*filename;
	char		*last_dot;

	original_filename_dup = ft_strdup(original_filename);
	if (!(last_dot = ft_strrchr(original_filename_dup, '.')))
	{
		filename = ft_strnew(ft_strlen(original_filename_dup)
			+ ft_strlen(ASM_FILE_EXTENSION));
		ft_strcat(filename, original_filename_dup);
	}
	else
	{
		filename = ft_strnew((last_dot - original_filename_dup)
			+ ft_strlen(ASM_FILE_EXTENSION));
		*last_dot = '\0';
		ft_strcat(filename, original_filename_dup);
	}
	ft_strcat(filename, ASM_FILE_EXTENSION);
	ft_strdel(&original_filename_dup);
	return (filename);
}

static int		open_output_file(const char *original_filename)
{
	int			fd;
	char		*filename;

	fd = 0;
	if (!(filename = determine_new_filename(original_filename)))
		die("Malloc error. Abording.");
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) <= 0)
		die("Unable to open output file. Abording.");
	ft_strdel(&filename);
	return (fd);
}

static void		write_header(int fd, const t_champion *champion)
{
	header_t	champ_header;

	ft_bzero(&champ_header, sizeof(header_t));
	ft_strcat(champ_header.prog_name, champion->name);
	ft_strcat(champ_header.comment, champion->comment);
	champ_header.magic = invertoctets(COREWAR_EXEC_MAGIC);
	write(fd, &champ_header, sizeof(header_t));
}

void			compile(const char *filename)
{
	int			file;

	puts("MEGALEL");
	file = open_output_file(filename);
	write_header(file, get_champion(0));
	write_commands(file, get_champion(0));
	close(file);
}
