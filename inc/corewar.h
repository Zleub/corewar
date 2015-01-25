/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 23:47:01 by adebray           #+#    #+#             */
/*   Updated: 2015/01/25 11:49:44 by adebray          ###   ########.fr       */
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
};

typedef struct s_process	t_process;

struct						s_process
{
	int						index;
};

t_process					*manage_process(int macro);

typedef struct s_process_list	t_process_list;

struct						s_process_list
{
	t_process				*p;
	t_process_list			*next;
};

void						*manage_process_list(int macro);

void						ft_exit(int i);

void						corewar_init(int argc, char **argv);
int							corewar_getopt(t_heros *heros);

void						read_header(int fd, t_heros *heros);
void						read_heros(int fd, t_heros *heros);

unsigned int				ft_hashich(char *line);
void						ft_dump(void);
int							invertbits(unsigned int x);

#endif
