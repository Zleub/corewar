#include <libft.h>
#include <ft_printf.h>
#include <env.h>
#include <corewar.h>

void		write_herostomemory(int offset, t_heros *heros)
{
	unsigned int m;
	t_memory *memory;

	m = 0;
	memory = manage_memory(GET);
	while (m < heros->h.prog_size)
	{
		memory->memory[offset + m].color = heros->color;
		memory->memory[offset + m].op = (unsigned char)heros->c[m];
		m += 1;
	}
}

int			main(int argc, char **argv)
{
	int			player_nbr;
	t_heros		heros[4];

	corewar_init(argc, argv);
	player_nbr = corewar_getopt(heros);

	int offset = MEM_SIZE / player_nbr;
	int i = 0;
	while (i < player_nbr)
	{
		write_herostomemory(offset * i, &heros[i]);
		i += 1;
	}

	manage_memory(PRINT);
	return (0);
}
