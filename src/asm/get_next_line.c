/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaurer <amaurer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 18:49:09 by amaurer           #+#    #+#             */
/*   Updated: 2014/01/17 14:15:40 by amaurer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <libft.h>
#include <unistd.h>
#include <fcntl.h>

static int	get_next_line_return(char **mem, char **line, int ret)
{
	char	*tmp;

	if (ret == -1)
		return (-1);
	if (!ret && ft_strlen(*mem))
	{
		*line = ft_strdup(*mem);
		tmp = *mem;
		*mem = ft_strnew(0);
		ft_strdel(&tmp);
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	char		buf[BUFF_SIZE + 1] = {0};
	int			ret;
	static char	*mem;
	char		*nl;
	char		*tmp;

	if (!line || (mem && (nl = ft_strchr(mem, '\n')) && (tmp = mem)))
	{
		if (!line || (*line = ft_strsub(mem, 0, nl - mem)) == NULL
			|| (mem = ft_strsub(mem, nl - mem + 1, ft_strlen(nl))) == NULL)
			return (-1);
		ft_strdel(&tmp);
		return (1);
	}
	else if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (mem || (mem = ft_strnew(0)))
		{
			tmp = mem;
			mem = ft_strjoin(mem, buf);
			ft_strdel(&tmp);
			return (get_next_line(fd, line));
		}
	}
	return (get_next_line_return(&mem, line, ret));
}
