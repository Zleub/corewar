/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 23:47:01 by adebray           #+#    #+#             */
/*   Updated: 2015/01/22 16:31:18 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <op.h>
# include <enum.h>
/*
** MANAGE_MEMORY
*/

typedef struct s_memory	t_memory;

struct					s_memory
{
	void				(*memory_callbacks[3]) (t_memory *);
	char				*memory;
	int					size;
};

typedef struct s_heros	t_heros;

struct					s_heros
{
	header_t			h;
	char				*c;
};

t_memory				*manage_memory(int macro);

#endif
