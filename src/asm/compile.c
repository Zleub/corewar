#include "asm.h"
#include "op.h"
#include <limits.h>
#include <fcntl.h>

int		invertoctets(int src)
{
	return ((src >> 24) & 0xff) |
		((src << 8) & 0xff0000) |
		((src >> 8) & 0xff00) |
		((src << 24) & 0xff000000);
}

void			write_header(int fd, const t_champion *champion)
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

static char		*determine_new_filename(const char *original_filename)
{
	char		*original_filename_dup;
	char		*filename;
	char		*last_dot;

	original_filename_dup = ft_strdup(original_filename);
	if (!(last_dot = ft_strrchr(original_filename_dup, '.')))
	{
		filename = ft_strnew(ft_strlen(original_filename_dup) + ft_strlen(ASM_FILE_EXTENSION));
		ft_strcat(filename, original_filename_dup);
	}
	else
	{
		filename = ft_strnew((last_dot - original_filename_dup) + ft_strlen(ASM_FILE_EXTENSION));
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
		die("Malloc error.");
	else if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC)) <= 0)
		die("Unable to open output file.");
	ft_strdel(&filename);
	return (fd);
}

void			compile(const char *filename)
{
	int			file;

	file = open_output_file(filename);
	write_header(file, get_champion(0));
}