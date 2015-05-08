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

static t_arg_type	get_arg_type(unsigned int pos, char coding_octet)
{
	if (pos == 3)
		return (coding_octet & (char)3);
	else if (pos == 2)
		return (coding_octet & (char)12);
	else if (pos == 1)
		return (coding_octet & (char)48);
	else if (pos == 0)
		return (coding_octet & (char)192);
	else
		return (T_DIR);
}

static size_t	get_arg_size(t_arg_type type, int mysterious_attribute)
{
	if (type == T_DIR && mysterious_attribute)
		return (DIR_SIZE / 2);
	else if (type == T_DIR)
		return (DIR_SIZE);
	else if (type == T_REG)
		return (REG_SIZE);
	else if (type == T_IND)
		return (IND_SIZE);
	return (0);
}

static int		extract_reg(const char *arg)
{
	return (ft_atoi(ft_strsub(arg, 1, ft_strlen(arg) - 1)));
}

static int		extract_lab(uint cmd_offset, char *lab)
{
	t_label		*lab_cur;
	t_command	*target_cmd;

	lab_cur = get_champion(0)->labels;
	while (lab_cur)
	{
		if (!ft_strcmp(lab_cur->name, lab))
		{
			target_cmd = lab_cur->target;
			return (target_cmd->offset - cmd_offset);
		}
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
		return (extract_lab(offset, lab));
	else
		return (ft_atoi(ft_strsub(arg, 1, ft_strlen(arg) - 1)));
}

static int		extract_ind(const char *arg)
{
	return (ft_atoi(arg));
}

static int		get_arg(t_arg_type type, const char *arg, uint offset)
{
	if (type == T_REG)
		return (extract_reg(arg));
	else if (type == T_DIR)
		return (extract_dir(arg, offset));
	else if (type == T_IND)
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
		arg_type = get_arg_type(i, (char)command->coding_octet);
		arg_size = get_arg_size(arg_type, command->op->unknown1);
		arg = get_arg(arg_type, command->raw_args[i], command->offset);
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
		ft_putendl("LELELLELELELELELELE");
		command = command->next;
	}
}

void			compile(const char *filename)
{
	int			file;

	file = open_output_file(filename);
	write_header(file, get_champion(0));
	write_commands(file, get_champion(0));
	close(file);
}