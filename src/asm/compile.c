#include "asm.h"
#include "op.h"
#include <limits.h>
#include <fcntl.h>
#include <stdio.h>

int		invertoctets(int src)
{
	char	*bytes;
	char	c;
	int		ret;

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

int				arg_to_big_endian(int arg, size_t arg_size)
{
	char	*bytes;
	char	c;
	int		ret;

	if (arg_size == 1)
		return (arg);
	else if (arg_size == 2)
	{
		bytes = (char *)&arg;
		c = bytes[0];
		bytes[0] = bytes[1];
		bytes[1] = c;
		ft_memcpy(&ret, bytes, sizeof(int));
		return (ret);
	}
	else if (arg_size == 4)
		return (invertoctets(arg));
	return (-1);
}

void			write_header(int fd, const t_champion *champion)
{
	header_t	champ_header;

	ft_bzero(&champ_header, sizeof(header_t));
	ft_strcat(champ_header.prog_name, champion->name);
	ft_strcat(champ_header.comment, champion->comment);
	champ_header.magic = invertoctets(COREWAR_EXEC_MAGIC);
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
		die("Malloc error. Abording.");
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) <= 0)
		die("Unable to open output file. Abording.");
	ft_strdel(&filename);
	return (fd);
}

static void		write_opcode(int fd, t_command *command)
{
	write(fd, &command->op->opcode, sizeof(char));
}

static void		write_coding_octet(int fd, t_command *command)
{
	if (command->op->coding_octet)
		write(fd, &command->coding_octet, sizeof(char));
}

static t_arg_type	get_arg_type(unsigned int pos, int coding_octet)
{
	if (pos == 3)
		return (coding_octet & 3);
	else if (pos == 2)
		return ((coding_octet & 12) >> 2);
	else if (pos == 1)
		return ((coding_octet & 48) >> 4);
	else if (pos == 0)
		return ((coding_octet & 192) >> 6);
	else
		return (T_DIR);
}

static size_t	get_arg_size(t_arg_type type, int mysterious_attribute)
{
	if (type == DIR_CODE && mysterious_attribute)
		return (DIR_ENCODING_SIZE / 2);
	else if (type == DIR_CODE)
		return (DIR_ENCODING_SIZE);
	else if (type == REG_CODE)
		return (REG_ENCODING_SIZE);
	else if (type == IND_CODE)
		return (IND_ENCODING_SIZE);
	return (0);
}

static int		extract_reg(const char *arg)
{
	return (ft_atoi(ft_strsub(arg, 1, ft_strlen(arg) - 1)));
}

static int		extract_lab(uint cmd_offset, char *lab)
{
	t_label		*lab_cur;
	static t_label		*praiveuh = NULL;
	t_command	*target_cmd;

	lab_cur = get_champion(0)->labels;
	praiveuh = lab_cur;
	while (lab_cur)
	{
		if (!ft_strcmp(lab_cur->name, lab))
		{
			printf("    %s <-> %p\n", lab_cur->name, lab_cur->target);
			if (lab_cur->target)
			{
				target_cmd = lab_cur->target;
				return (target_cmd->offset - cmd_offset);
			}
			else if (!lab_cur->target)
			{
				if (!lab_cur->next)
				{
					target_cmd = praiveuh->target;
					while (target_cmd->next)
						target_cmd = target_cmd->next;
					return (target_cmd->offset - cmd_offset + 3);
				}
				lab_cur = lab_cur->next;
				target_cmd = lab_cur->target;
				return (target_cmd->offset - cmd_offset);
			}
		}
		praiveuh = lab_cur;
		lab_cur = lab_cur->next;
	}
	ft_putstr(lab);
	die(" : label not found. Abording.");
	return (0);
}

static int		extract_dir(const char *arg, uint offset)
{
	char		*lab;

	if ((lab = ft_strchr(arg, LABEL_CHAR)))
		return (extract_lab(offset, lab + 1));
	else
		return (ft_atoi(ft_strsub(arg, 1, ft_strlen(arg) - 1)));
}

static int		extract_ind(const char *arg)
{
	return (ft_atoi(arg));
}

static int		get_arg(t_arg_type type, const char *arg, uint offset)
{
	if (type == REG_CODE)
		return (extract_reg(arg));
	else if (type == DIR_CODE)
		return (extract_dir(arg, offset));
	else if (type == IND_CODE)
		return (extract_ind(arg));
	return (0);
}

static void		write_parameters(int fd, t_command *command)
{
	unsigned int	i;
	t_arg_type		arg_type;
	size_t			arg_size;
	int				arg;

	i = 0;
	arg = 0;
	while (i < command->op->arg_number)
	{
		arg_type = get_arg_type(i, command->coding_octet);
		arg_size = get_arg_size(arg_type, command->op->unknown1);
		arg = arg_to_big_endian(get_arg(arg_type, command->raw_args[i], command->offset), arg_size);
		write(fd, &arg, arg_size);
		++i;
	}
}

void			write_commands(int fd, t_champion *champion)
{
	t_command	*command;

	command = champion->commands;
	while (command)
	{
		write_opcode(fd, command);
		write_coding_octet(fd, command);
		write_parameters(fd, command);
		command = command->next;
	}
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