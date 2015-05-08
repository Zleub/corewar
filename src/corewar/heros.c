/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heros.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/18 13:01:37 by adebray           #+#    #+#             */
/*   Updated: 2015/05/08 14:53:27 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		invertbits(unsigned int x)
{
	unsigned int tmp;

	tmp = 0;
	((char*)&tmp)[3] = ((char*)&x)[0];
	((char*)&tmp)[2] = ((char*)&x)[1];
	((char*)&tmp)[1] = ((char*)&x)[2];
	((char*)&tmp)[0] = ((char*)&x)[3];
	return (tmp);
}

void		read_header(int fd, t_heros *heros)
{
	static int		hnbr;

	if (hnbr == 0)
		hnbr = 1;
	read(fd, &heros->head, sizeof(header_t));
	heros->head.magic = invertbits(heros->head.magic);
	heros->head.prog_size = invertbits(heros->head.prog_size);
	heros->color = hnbr;
	heros->number = hnbr;
	hnbr += 1;
}

void		read_heros(int fd, t_heros *heros)
{
	if (!(heros->content = (char *)malloc(sizeof(char) * heros->head.prog_size)))
		exit(EXIT_FAILURE);
	read(fd, heros->content, heros->head.prog_size);
}

void		get_heros(char *file)
{
	static int	count;
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		write(2, file, ft_strlen(file));
		write(2, ": ", 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		read_header(fd, &g_heros[count]);
		read_heros(fd, &g_heros[count]);
		ft_bzero(&g_heros[count + 1], sizeof(t_heros));
		count += 1;
	}
}
