/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 23:07:06 by adebray           #+#    #+#             */
/*   Updated: 2015/01/23 23:13:56 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <corewar.h>

void		read_header(int fd, t_heros *heros)
{
	read(fd, &heros->h, sizeof(header_t));
	heros->h.magic = invertbits(heros->h.magic);
	heros->h.prog_size = invertbits(heros->h.prog_size);
	heros->color = ft_hashich(heros->h.prog_name);
}

void		read_heros(int fd, t_heros *heros)
{
	heros->c = (char *)malloc(sizeof(char) * heros->h.prog_size);
	read(fd, heros->c, heros->h.prog_size);
}
