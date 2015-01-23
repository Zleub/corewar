/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 23:47:01 by adebray           #+#    #+#             */
/*   Updated: 2015/01/23 23:09:39 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <op.h>
# include <enum.h>
/*
** MANAGE_MEMORY
*/

typedef struct s_cell	t_cell;

struct					s_cell
{
	char				op;
	char				color;
};

typedef struct s_memory	t_memory;

struct					s_memory
{
	void				(*memory_callbacks[3]) (t_memory *);
	struct s_cell		*memory;
	int					size;
};

t_memory				*manage_memory(int macro);
void					print_memory(t_memory *memory);

typedef struct s_heros	t_heros;

struct					s_heros
{
	header_t			h;
	char				*c;
	char				color;
};

void				corewar_init(int argc, char **argv);
int					corewar_getopt(t_heros *heros);

void				read_header(int fd, t_heros *heros);
void				read_heros(int fd, t_heros *heros);

unsigned int		ft_hashich(char *line);
void				ft_dump(void);
int					invertbits(unsigned int x);

#endif
