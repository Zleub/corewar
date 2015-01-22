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
	ft_printf("COREWAR_EXEC_MAGIC: %x\n", COREWAR_EXEC_MAGIC);
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

int		invertbits(unsigned int x)
{
	unsigned int test = 0;

	((char*)&test)[3] = ((char*)&x)[0];
	((char*)&test)[2] = ((char*)&x)[1];
	((char*)&test)[1] = ((char*)&x)[2];
	((char*)&test)[0] = ((char*)&x)[3];
	return (test);
}

int			main(int argc, char **argv)
{
	t_env		*env;
	t_heros		heros[4];

	// header_t	plaiz;

	ft_dump();
	manage_memory(INIT);
	manage_memory(NEW);
	t_memory *memory = manage_memory(GET);

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
		read(fd, &plaiz, sizeof(header_t));

		plaiz.magic = invertbits(plaiz.magic);
		ft_printf("%x\n", plaiz.magic);
		ft_printf("%s\n", plaiz.prog_name);
		plaiz.prog_size = invertbits(plaiz.prog_size);
		ft_printf("%d\n", plaiz.prog_size);
		ft_printf("%s\n", plaiz.comment);

		char str[plaiz.prog_size];
		read(fd, &str, plaiz.prog_size);

		unsigned int k;
		for(k = 0; k < plaiz.prog_size;k++)
		{
			// ft_printf("%s\n", str);
			memory->memory[k] = (unsigned char)str[k];
			ft_printf("%x ", str[k]);
		}
		ft_printf("\n");


		manage_env(NEXT);
	}

	manage_memory(PRINT);
	return (0);
}
