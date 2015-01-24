/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 23:05:48 by adebray           #+#    #+#             */
/*   Updated: 2015/01/24 02:00:08 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

unsigned int		ft_hashich(char *line)
{
	unsigned int	hashich;
	int				c;

	hashich = 5381;
	while ((c = *line++))
		hashich = ((hashich << 5) + hashich) ^ c;
	if (hashich > 231)
		hashich = hashich % 231;
	if (hashich < 17)
		hashich += 17;
	return (hashich);
}

int		invertbits(unsigned int x)
{
	unsigned int test = 0;

	((char*)&test)[3] = ((char*)&x)[0];
	((char*)&test)[2] = ((char*)&x)[1];
	((char*)&test)[1] = ((char*)&x)[2];
	((char*)&test)[0] = ((char*)&x)[3];
	return (test);
}

void	ft_exit(int i)
{
	endwin();
	exit(i);
}
