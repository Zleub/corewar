/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/04 20:38:47 by adebray           #+#    #+#             */
/*   Updated: 2015/02/04 21:21:58 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		corewar_check_size(void)
{
	if (REG_SIZE > 4)
		write(2, "Warning: REG_SIZE can overflow system type int\n", 47);
	if (DIR_SIZE > 4)
		write(2, "Warning: DIR_SIZE can overflow system type int\n", 47);
	if (IND_SIZE > 4)
		write(2, "Warning: IND_SIZE can overflow system type int\n", 47);
}

void		corewar_check_code(void)
{
	if (REG_CODE > 3 || DIR_CODE > 3 || IND_CODE > 3)
		write(2, "Warning: _CODE overflow CODING capacity\n", 40);
	if (REG_CODE == DIR_CODE)
		write(2, "Warning: same REG_CODE & DIR_CODE\n", 34);
	if (REG_CODE == IND_CODE)
		write(2, "Warning: same REG_CODE & IND_CODE\n", 34);
	if (DIR_CODE == IND_CODE)
		write(2, "Warning: same DIR_CODE & IND_CODE\n", 34);
}

void		corewar_check_vmparam(void)
{
	if (MAX_ARGS_NUMBER <= 0)
		write(2, "Warning: MAX_ARGS_NUMBER <= 0\n", 30);
	if (MAX_ARGS_NUMBER > 4)
		write(2, "Warning: MAX_ARGS_NUMBER out of specifications\n", 47);
	if (MAX_PLAYERS <= 0)
		write(2, "Warning: MAX_PLAYERS <= 0\n", 26);
	if (MAX_PLAYERS > 4)
		write(2, "Warning: MAX_PLAYERS out of specifications\n", 43);
	if (MAX_PLAYERS > 255)
		write(2, "Warning: MAX_PLAYERS out of char size ... Really ?\n", 43);
	if (MEM_SIZE <= 0)
		write(2, "Warning: MEM_SIZE <= 0\n", 23);
	if (REG_NUMBER <= 0)
		write(2, "Warning: REG_NUMBER <= 0\n", 25);
	if (CYCLE_TO_DIE <= 0)
		write(2, "Warning: CYCLE_TO_DIE <= 0\n", 27);
	if (CYCLE_DELTA <= 0)
		write(2, "Warning: CYCLE_DELTA <= 0\n", 26);
	if (NBR_LIVE <= 0)
		write(2, "Warning: NBR_LIVE <= 0\n", 23);
	if (MAX_CHECKS <= 0)
		write(2, "Warning: MAX_CHECKS <= 0\n", 25);
}

void		corewar_check(void)
{
	corewar_check_size();
	corewar_check_code();

	if (REG_ENCODING_SIZE != 1 || IND_ENCODING_SIZE != 2 || DIR_ENCODING_SIZE != 4)
		write(2, "Warning: _ENCODING_SIZE out of zaz\'s proportions\n", 47);

	corewar_check_vmparam();

	if (T_REG == T_DIR)
		write(2, "Warning: same T_REG & T_DIR\n", 28);
	if (T_REG == T_IND)
		write(2, "Warning: same T_REG & T_IND\n", 28);
	if (T_DIR == T_IND)
		write(2, "Warning: same T_DIR & T_IND\n", 28);

	if (PROG_NAME_LENGTH <= 0)
		write(2, "Warning: PROG_NAME_LENGTH <= 0\n", 31);
	if (COMMENT_LENGTH <= 0)
		write(2, "Warning: COMMENT_LENGTH <= 0\n", 29);
	if (COREWAR_EXEC_MAGIC <= 0)
		write(2, "Warning: COREWAR_EXEC_MAGIC <= 0\n", 33);
}
