#include <libft.h>
#include <ft_printf.h>
#include <env.h>
#include <op.h>
#include <corewar.h>

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

int			main(int argc, char **argv)
{
	t_env	*env;

	env = manage_env(GET);
	env->argc = argc;
	env->argv = argv;
	env->format = "-dump:-n:-n:-n:-n:";

	manage_env(PRINT);

	ft_printf("\n");

	manage_env(NEXT);
	while (env->opt[0] != '\0' && env->opt[0] != '?')
	{
		ft_printf("opt: %s, arg: %s\n", env->opt, env->arg);
		manage_env(NEXT);
	}

	ft_printf("\n");
	ft_dump();
	manage_memory(INIT);
	manage_memory(NEW);

	t_memory *memory = manage_memory(GET);
	memory->memory[0] = 11;
	memory->memory[3] = 1;
	memory->memory[1024] = 12;

	// manage_memory(PRINT);
	return (0);
}
