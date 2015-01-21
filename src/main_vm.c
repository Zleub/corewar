#include <libft.h>
#include <ft_printf.h>
#include <env.h>
#include <op.h>
#include <corewar.h>
#include <fcntl.h>

void		ft_dump(void)
{
	ft_printf("foreach PROCESS: \n");
	ft_printf("REG_NUMBER: %d\n", REG_NUMBER);
	ft_printf("REG_SIZE: %d\n", REG_SIZE);
	ft_printf("Program Counter: \n");
	ft_printf("carry : \n");
	ft_printf("NAME_CMD_STRING: %s\n", NAME_CMD_STRING);
	ft_printf("COMMENT_CMD_STRING: %s\n", COMMENT_CMD_STRING);
	ft_printf("PROG_NAME_LENGTH: %d\n", PROG_NAME_LENGTH);
	ft_printf("COMMENT_LENGTH: %d\n", COMMENT_LENGTH);
	ft_printf("COREWAR_EXEC_MAGIC: %d\n", COREWAR_EXEC_MAGIC);
	ft_printf("\nVM: \n");
	ft_printf("VM per PROCESS: \n");
	ft_printf("CYCLE_TO_DIE: %d\n", CYCLE_TO_DIE);
	ft_printf("NBR_LIVE: %d\n", NBR_LIVE);
	ft_printf("CYCLE_DELTA: %d\n", CYCLE_DELTA);
	ft_printf("MAX_PLAYERS: %d\n", MAX_PLAYERS);
	ft_printf("MEM_SIZE: %d\n", MEM_SIZE);
	ft_printf("IDX_MOD: %d\n", IDX_MOD);
	ft_printf("CHAMP_MAX_SIZE: %d\n", CHAMP_MAX_SIZE);
}

void		ft_getfile(int fd)
{
	ft_printf("fd: %d\n", fd);

	ft_bzero(manage_file(SET), 80);
	while (read(fd, (char**)manage_file(SET), 80) > 0)
	{
		manage_file(ADD);
		ft_bzero(manage_file(SET), 80);
	}
}

int		ft_isfile(t_env *env)
{
	int fd;

	if (!ft_strcmp(env->opt, "n"))
	{
		if ((fd = open(env->arg, O_RDONLY)) == -1)
		{
			ft_printf("Open error\n");
			return (-1);
		}
		else
			return (fd);
	}
	return (-1);
}

int			main(int argc, char **argv)
{
	t_env	*env;
	header_t	plaiz;

	env = manage_env(GET);
	env->argc = argc;
	env->argv = argv;
	env->format = "-n:-n:-n:-n:";
	manage_env(PRINT);
	ft_printf("\n");
	manage_env(NEXT);
	while (env->opt[0] != '\0' && env->opt[0] != '?')
	{
		ft_printf("opt: %s, arg: %s\n", env->opt, env->arg);
		int fd = ft_isfile(env);
		// char str[4 + PROG_NAME_LENGTH + 1 + 4 + COMMENT_LENGTH + 1];
		read(fd, &plaiz, 4 + PROG_NAME_LENGTH + 1 + 4 + COMMENT_LENGTH + 1);

		// ft_printf("%d\n", plaiz.magic);
		int i = 3;
		while (i >= 0) {
			ft_printf("%d, ", ((char*)(&(plaiz.magic)))[i]);
			i -= 1;
		}
		ft_printf("\n");
		ft_printf("%s\n", plaiz.prog_name);
		// ft_printf("%d\n", plaiz.prog_size);
		i = 0;
		while (i < 4) {
			ft_printf("%d, ", ((char*)(&(plaiz.prog_size)))[i]);
			i += 1;
		}
		ft_printf("\n");
		ft_printf("%s\n", plaiz.comment);
		// write(1, str, 4 + PROG_NAME_LENGTH + 1 + 4 + COMMENT_LENGTH + 1);

		// manage_file(PRINTBINARY);
		// manage_file(66);
		// (*(t_file**)manage_file(GET)) = NULL;
		manage_env(NEXT);
	}

	ft_dump();
	// 	manage_memory(INIT);
	// manage_memory(NEW);

	// t_memory *memory = manage_memory(GET);
	// memory->memory[0] = 11;
	// memory->memory[3] = 1;
	// memory->memory[1024] = 12;

	// manage_memory(PRINT);
	return (0);
}
