#include <corewar.h>

void	print_external(void)
{
	extern char *cst;

	dprintf(OUT, "%s\n", cst);
}
