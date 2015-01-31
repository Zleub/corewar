/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manageenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adebray <adebray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/27 08:15:56 by adebray           #+#    #+#             */
/*   Updated: 2015/01/31 14:12:34 by adebray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>

char				is_separator(char in)
{
	int		i;
	char	*separators;

	i = 0;
	separators = SEPARATORS;
	while (separators[i])
	{
		if (in == separators[i])
			return (1);
		i += 1;
	}
	return (0);
}

char				manage_envgetoptend(char *format)
{
	int j = 1;
	while (format[j] && is_separator(format[j]) == 0)
		j += 1;
	if (format[j] == ':')
		return (1);
	else
		return (0);
}

int					manage_envnextindex(char *format)
{
	int k = 1;
	while (format[k] && format[k] != '-')
		k += 1;
	return (k);
}

char				*manage_envgetopt(char *format)
{
	int				i;
	static char		opt[80];

	i = 0;
	ft_bzero(opt, 80);
	while (format[i] && is_separator(format[i + 1]) == 0)
	{
		opt[i] = format[i + 1];
		i += 1;
	}
	opt[i] = '\0';
	return (opt);
}
void				manage_envget(t_env *env)
{
	static int		argcount;
	static int		index;

	argcount += 1;

	if (argcount >= env->argc)
	{
		env->opt = "?";
		return ;
	}

	if (!ft_strcmp(manage_envgetopt(&env->format[index]), &env->argv[argcount][1]))
		env->opt = manage_envgetopt(&env->format[index]);
	else
		env->opt = "?";

	if (manage_envgetoptend(&env->format[index]) == 0)
		env->arg = "";
	else
	{
		argcount += 1;
		env->arg = env->argv[argcount];
	}
	index += manage_envnextindex(&env->format[index]);
}

t_env				*manage_env(int macro)
{
	static t_env	env;

	if (macro == GET)
		return (&env);
	else if (macro == NEXT)
		manage_envget(&env);
	else if (macro == PRINT)
	{
		ft_printf("argc: \t\t%d\n", env.argc);
		ft_printf("argv: \t\t%p\n", env.argv);
		ft_printf("format: \t%s\n", env.format);
		ft_printf("opt: \t\t%s\n", env.opt);
		ft_printf("arg: \t\t%s\n", env.arg);
	}
	else
		ft_printf("Useless call to manageenv\n");
	return (NULL);
}
