/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 18:36:41 by adebray           #+#    #+#             */
/*   Updated: 2015/02/18 18:38:37 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	draw(void)
{

}

void	update(int dt)
{
	(void)dt;
}

void	init_corewar(int player_nbr)
{
	g_process = NULL;
	init_memory(player_nbr);
}
