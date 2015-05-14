/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/17 12:19:46 by adebray           #+#    #+#             */
/*   Updated: 2015/05/14 07:55:35 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <libft.h>
# include <ft_printf.h>

# include <limits.h>
# include <errno.h>
# include <fcntl.h>
# include <op.h>

typedef struct s_corewar	t_corewar;

struct						s_corewar
{
	int						dump;
	int						verb;
	int						cycle_counter;
	int						tic_rate;
	int						cycles_todie;
	unsigned int			*scores;
	int						player_nbr;
	int						last_alive;
	int						process_nbr;
};

t_corewar					g_corewar;

int							max_size(void);
void						die(int end);
void						draw(void);
void						update(int dt);
int							init_corewar(int player_nbr);

/*
** Debug
*/
# include <stdio.h>

# define OUT 1

void		print_clean_hexa(unsigned char c);

/*
** Memory
*/

typedef struct s_cell		t_cell;

struct						s_cell
{
	char					op;
	char					p; // IS A PROCESS HEAD ON THAT CELL
	char					c; // COLOR IF A PROCESS HAS WRITE
};

t_cell						g_memory[MEM_SIZE];

void						init_memory(int player_nbr);
void						dump_memory(void);
int							write_memory(int index, char *str, int len);


/*
** Player
*/


typedef struct s_heros		t_heros;

struct						s_heros
{
	header_t				head;
	char					*content;
	char					color;
	int						number;
};

t_heros						g_heros[MAX_PLAYERS];

int							invertbits(unsigned int i);
void						read_header(int, t_heros *);
void						read_heros(int fd, t_heros *heros);
void						get_heros(char *file);

/*
** Processus
*/

typedef struct s_process	t_process;

struct						s_process
{
	int						lives;
	int						delay;
	int						index;
	int						carry;
	char					registers[REG_NUMBER][REG_SIZE];
	int						number;
	int						p_number;
	t_process				*next;
};

t_process					*g_process;

void						add_process(t_process *elem);
t_process					*new_process(t_process *elem);
void						print_process(t_process *head);
void						update_process(t_process *head);
int							write_registers(int index, t_process *p, char *str, int len);
int							write_registers_reverse(int index, t_process *p, char *str, int len);

/*
** Intruction
*/

typedef struct s_instruct	t_instruction;

struct						s_instruct
{
	int						type;
	int						size;
	char					*args;
};

t_instruction				g_instruction[MAX_ARGS_NUMBER];

# define GET_(X) (X)get_int

t_op						get_op(t_process *p);
void						print_op(t_op op);
void						init_instruction(int max);
int							fill_instruction(t_process *p);
void						print_instruction();
void						print_instruction_decimal();
int							get_int(t_instruction *i);
void						reset_instruction(void);
char						*get_register(t_process *p, t_instruction *i);

/**/
typedef union u_type		t_type;

union						u_type
{
	char					c;
	short					s;
	int						i;
};
/**/

char						*g_array[MAX_ARGS_NUMBER];

void						cpy_register(t_process *p, t_instruction *inst, char str[DIR_SIZE]);
void						cpy_memory(t_process *p, t_instruction *inst, char str[DIR_SIZE]);
void						cpy_value(t_process *p, t_instruction *inst, char str[DIR_SIZE]);
void						init_array(void);
void						fill_array(t_process *p);

#endif
