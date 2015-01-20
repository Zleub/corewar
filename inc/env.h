/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 08:15:08 by adebray           #+#    #+#             */
/*   Updated: 2015/01/20 06:47:36 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <enum.h>
# include <ft_printf.h>
# include <libft.h>

# define SEPARATORS "[:-]"

/*
** OPTGET STRING FORMAT: "-x:-y:" != "-abc:" != "-a-b[-c:]" != "[-a:]-b-c:"
** -arg is bool type | -arg: is string type
** [] is for optional argumentation
*/

typedef struct	s_env
{
	int			argc;
	char		**argv;
	char		*format;

	char		*opt;
	char		*arg;
}				t_env;

t_env			*manage_env(int macro);

typedef struct	s_file
{
	char		*str;
	void		*next;
}				t_file;

void			*manage_file(int macro);

#endif
