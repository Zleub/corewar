/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/23 23:07:58 by adebray           #+#    #+#             */
/*   Updated: 2015/02/04 20:39:06 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void		ncurse_init(void)
{
	stdscr = initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	assume_default_colors(235, COLOR_BLACK);
}

void			corewar_init(int argc, char **argv)
{
	t_env		*env;

	manage_memory(INIT);
	manage_memory(NEW);
	env = manage_env(GET);
	env->argc = argc;
	env->argv = argv;
	env->format = "-n:-n:-n:-n:";
}

int			ft_isfile(t_env *env)
{
	int		fd;

	if (!ft_strcmp(env->opt, "n"))
	{
		if ((fd = open(env->arg, O_RDONLY)) == -1)
		{
			write(2, env->arg, ft_strlen(env->arg));
			write(2, ": ", 2);
			die(errno);
		}
		else
			return (fd);
	}
	return (-1);
}

int		corewar_getopt(t_heros *heros, int *ncurse)
{
	int			fd;
	int			i;
	t_env		*env;

	env = manage_env(GET);
	manage_env(NEXT);
	i = 0;
	fd = 0;
	while (env->opt[0] != '\0' && env->opt[0] != '?')
	{
		ft_printf("opt: %s, arg: %s\n", env->opt, env->arg);
		fd = ft_isfile(env);
		if (fd != -1) {
			read_header(fd, &heros[i]);
			read_heros(fd, &heros[i]);
			i += 1;
		}
		if (!ft_strcmp(env->opt, "ncurse"))
		{
			ft_printf("tet\n");
			*ncurse = 1;
		}
		manage_env(NEXT);
	}
	return (i);
}
