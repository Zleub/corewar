/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 23:47:01 by adebray           #+#    #+#             */
/*   Updated: 2015/02/04 05:03:43 by adebray          ###   ########.fr       */
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

enum	e_opstyle
{
	REG = 64,
	DIR = 128,
	IND = 192,
	REG_REG = 80,
	REG_DIR = 96,
	REG_IND = 112,
	DIR_REG = 144,
	DIR_DIR = 160,
	DIR_IND = 176,
	IND_REG = 208,
	IND_DIR = 224,
	IND_IND = 240,
	REG_REG_REG = 84,
	REG_REG_DIR = 88,
	REG_REG_IND = 92,
	REG_DIR_REG = 100,
	REG_DIR_DIR = 104,
	REG_DIR_IND = 108,
	REG_IND_REG = 116,
	REG_IND_DIR = 120,
	REG_IND_IND = 124,
	DIR_REG_REG = 148,
	DIR_REG_DIR = 152,
	DIR_REG_IND = 156,
	DIR_DIR_REG = 164,
	DIR_DIR_DIR = 168,
	DIR_DIR_IND = 172,
	DIR_IND_REG = 180,
	DIR_IND_DIR = 184,
	DIR_IND_IND = 188,
	IND_REG_REG = 212,
	IND_REG_DIR = 216,
	IND_REG_IND = 220,
	IND_DIR_REG = 228,
	IND_DIR_DIR = 232,
	IND_DIR_IND = 236,
	IND_IND_REG = 244,
	IND_IND_DIR = 248,
	IND_IND_IND = 252
};

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
	int						index;
	int						pc;
	char					*registers[REG_NUMBER];
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

void						die(int i);

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
