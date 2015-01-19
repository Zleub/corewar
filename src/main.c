#include <libft.h>
#include <op.h>

#define ENDL ft_putstr("\n")

#define DUMPINT(x) ft_putnbr(x)

void		ft_dump(void)
{
	ft_putstr("foreach PROCESS: \n");
	ENDL;
	ft_putstr("REG_NUMBER: ");
	DUMPINT(REG_NUMBER);
	ENDL;
	ft_putstr("REG_SIZE: ");
	DUMPINT(REG_SIZE);
	ENDL;
	ft_putstr("Program Counter: ");
	ENDL;
	ft_putstr("carry : ");
	ENDL;
	ENDL;
	ft_putstr("VM: \n");
	ENDL;
	ft_putstr("VM per PROCESS: \n");
	ft_putstr("CYCLE_TO_DIE");
	ENDL;
	ft_putstr("")
}

int			main(void)
{
	ft_putstr("Hello !\n");
	ft_dump();
	return (0);
}
