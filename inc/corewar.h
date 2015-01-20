/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/19 23:47:01 by adebray           #+#    #+#             */
/*   Updated: 2015/01/20 04:18:51 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

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

t_memory				*manage_memory(int macro);

#endif
