/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 23:47:01 by adebray           #+#    #+#             */
/*   Updated: 2015/02/15 18:15:04 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <libft.h>
# include <ft_printf.h>
# include <errno.h>
# include <op.h>
# include <enum.h>
# include <env.h>
# include <ncurses.h>

/*
** MANAGE_MEMORY
*/

typedef struct s_cell		t_cell;

struct						s_cell
{
	char					op;
	char					proc;
	char					colorp;
};

typedef struct s_memory		t_memory;

struct						s_memory
{
	void					(*memory_callbacks[3]) (t_memory *);
	struct s_cell			*memory;
	int						size;
};

t_memory					*manage_memory(int macro);
void						print_memory(t_memory *memory);

typedef struct s_heros		t_heros;

struct						s_heros
{
	header_t				h;
	char					*c;
	char					color;
	int						number;
};

typedef struct s_process	t_process;

struct						s_process
{
	int						delay;
	int						index;
	int						pc;
	unsigned char			*registers[REG_NUMBER];
	int						carry;
	int						number;
};

t_process					*manage_process(int macro);

typedef struct s_process_list	t_process_list;

struct						s_process_list
{
	t_process				*p;
	t_process_list			*next;
};

void						*manage_process_list(int macro);

typedef struct s_arguments	t_arguments;

struct						s_arguments
{
	int						coding_octet;
	int						magic;
	int						count;
	int						index;
	int						size;
	int						type;
};

void						*manage_arguments(int macro);

void						die(int i);

void						corewar_check(void);
void						corewar_init(int argc, char **argv);

int							corewar_getopt(t_heros *heros, int *ncurse);
void						write_heros(int offset, t_heros *heros);
void						foreach_heros(int player_nbr, t_heros *heros);

void						read_header(int fd, t_heros *heros);
void						read_heros(int fd, t_heros *heros);

unsigned int				ft_hashich(char *line);
void						ft_dump(void);
int							invertbits(unsigned int x);

void						increment_process(void);
void						ncurse_init(void);

#endif
