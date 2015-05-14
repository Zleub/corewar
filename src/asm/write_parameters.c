/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsierra- <nsierra-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/14 03:01:25 by nsierra-          #+#    #+#             */
/*   Updated: 2015/05/14 03:01:27 by nsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int			invertoctets(int src)
{
	char			*bytes;
	char			c;
	int				ret;

	bytes = (char *)&src;
	c = bytes[3];
	bytes[3] = bytes[0];
	bytes[0] = c;
	c = bytes[1];
	bytes[1] = bytes[2];
	bytes[2] = c;
	ft_memcpy(&ret, bytes, sizeof(int));
	return (ret);
}

static int			arg_to_big_endian(int arg, size_t arg_size)
{
	char			*bytes;
	char			c;
	int				ret;

	if (arg_size == 1)
		return (arg);
	else if (arg_size == 2)
	{
		bytes = (char *)&arg;
		c = bytes[0];
		bytes[0] = bytes[1];
		bytes[1] = c;
		ft_memcpy(&ret, bytes, sizeof(int));
		return (ret);
	}
	else if (arg_size == 4)
		return (invertoctets(arg));
	return (-1);
}

static t_arg_type	get_arg_type(unsigned int pos, int coding_octet)
{
	if (pos == 3)
		return (coding_octet & 3);
	else if (pos == 2)
		return ((coding_octet & 12) >> 2);
	else if (pos == 1)
		return ((coding_octet & 48) >> 4);
	else if (pos == 0)
		return ((coding_octet & 192) >> 6);
	else
		return (T_DIR);
}

static size_t		get_arg_size(t_arg_type type, int mysterious_attribute)
{
	if (type == DIR_CODE && mysterious_attribute)
		return (DIR_ENCODING_SIZE / 2);
	else if (type == DIR_CODE)
		return (DIR_ENCODING_SIZE);
	else if (type == REG_CODE)
		return (REG_ENCODING_SIZE);
	else if (type == IND_CODE)
		return (IND_ENCODING_SIZE);
	return (0);
}

void				write_parameters(int fd, t_command *command)
{
	unsigned int	i;
	t_arg_type		arg_type;
	size_t			arg_size;
	int				arg;

	i = 0;
	arg = 0;
	while (i < command->op->arg_number)
	{
		arg_type = get_arg_type(i, command->coding_octet);
		arg_size = get_arg_size(arg_type, command->op->unknown1);
		arg = arg_to_big_endian(get_arg(arg_type, command->raw_args[i],
			command->offset), arg_size);
		write(fd, &arg, arg_size);
		++i;
	}
}
