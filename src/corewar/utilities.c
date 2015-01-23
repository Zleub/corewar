/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 23:05:48 by adebray           #+#    #+#             */
/*   Updated: 2015/01/23 23:07:36 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include <corewar.h>

unsigned int		ft_hashich(char *line)
{
	unsigned int	hashich;
	int				c;

	hashich = 5381;
	while ((c = *line++))
		hashich = ((hashich << 5) + hashich) ^ c;
	if (hashich > 255)
		return (hashich % 255);
	return (hashich);
}

void		ft_dump(void)
{
	ft_printf("foreach PROCESS: \n");
	ft_printf("REG_NUMBER: %d\n", REG_NUMBER);
	ft_printf("REG_SIZE: %d\n", REG_SIZE);
	ft_printf("Program Counter: \n");
	ft_printf("carry : \n");
	ft_printf("NAME_CMD_STRING: %s\n", NAME_CMD_STRING);
	ft_printf("COMMENT_CMD_STRING: %s\n", COMMENT_CMD_STRING);
	ft_printf("PROG_NAME_LENGTH: %d\n", PROG_NAME_LENGTH);
	ft_printf("COMMENT_LENGTH: %d\n", COMMENT_LENGTH);
	ft_printf("COREWAR_EXEC_MAGIC: %x\n", COREWAR_EXEC_MAGIC);
	ft_printf("\nVM: \n");
	ft_printf("VM per PROCESS: \n");
	ft_printf("CYCLE_TO_DIE: %d\n", CYCLE_TO_DIE);
	ft_printf("NBR_LIVE: %d\n", NBR_LIVE);
	ft_printf("CYCLE_DELTA: %d\n", CYCLE_DELTA);
	ft_printf("MAX_PLAYERS: %d\n", MAX_PLAYERS);
	ft_printf("MEM_SIZE: %d\n", MEM_SIZE);
	ft_printf("IDX_MOD: %d\n", IDX_MOD);
	ft_printf("CHAMP_MAX_SIZE: %d\n", CHAMP_MAX_SIZE);
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
