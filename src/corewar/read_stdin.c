/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 23:07:06 by adebray           #+#    #+#             */
/*   Updated: 2015/01/29 18:12:15 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_printf.h>
#include <corewar.h>
#include <ncurses.h>

void		read_header(int fd, t_heros *heros)
{
	static int		hnbr;

	if (hnbr == 0)
		hnbr = 1;
	read(fd, &heros->h, sizeof(header_t));
	heros->h.magic = invertbits(heros->h.magic);
	heros->h.prog_size = invertbits(heros->h.prog_size);
	heros->color = hnbr;

	hnbr += 1;
}

void		read_heros(int fd, t_heros *heros)
{
	heros->c = (char *)malloc(sizeof(char) * heros->h.prog_size);
	read(fd, heros->c, heros->h.prog_size);
}