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
	manage_file(NEW);
	while (get_next_line(fd, (char**)manage_file(SET)) > 0)
		manage_file(ADD);
}

void		ft_isfile(t_env *env)
{
	int fd;

	if (!ft_strcmp(env->opt, "n"))
	{
		if ((fd = open(env->arg, O_RDONLY)) == -1)
		{
			ft_printf("Open error\n");
			return ;
		}
		else
			ft_getfile(fd);
	}
}

int			main(int argc, char **argv)
{
	t_env	*env;

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
		ft_isfile(env);
		manage_file(PRINTBINARY);
		manage_env(NEXT);
	}
	return (0);
}
