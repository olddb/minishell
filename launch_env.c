/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 19:52:04 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/16 14:46:04 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int			add_to_env(char *str, int i, t_env *e)
{
	char	**new_env;
	int		j;
	int		z;

	j = 0;
	z = 0;
	new_env = (char **)malloc(sizeof(new_env) * i + 29);
	while (j < i)
	{
		if (ft_memcmp(e->envp[j], str, ft_strlen(str)) == 0)
		{
			str = (e->arg[2]) ? ft_strjoin(str, e->arg[2]) : str;
			new_env[j++] = ft_strdup(str);
			z = 1;
		}
		new_env[j] = (e->envp[j]) ? ft_strdup(e->envp[j]) : new_env[j];
		if (j++, j >= i && z != 1)
		{
			str = (e->arg[2]) ? ft_strjoin(str, e->arg[2]) : str;
			new_env[j++] = ft_strdup(str);
		}
	}
	e->envp = new_env;
	return (j);
}

void		arg_handler(t_env *e)
{
	char	**new_arg;
	char	*arg;
	int		new_nb_arg;
	int		i;
	int		j;

	i = 0;
	j = 2;
	if (e->nb_arg - 2 <= 0)
		return ;
	new_nb_arg = e->nb_arg - 2;
	new_arg = (char **)malloc(sizeof(new_arg) * new_nb_arg);
	while (new_nb_arg > i)
	{
		arg = ft_strdup(e->arg[j]);
		new_arg[i] = arg;
		i++;
	}
	free(e->arg);
	e->arg = new_arg;
}

void		env_i(t_env *e)
{
	e->is_env_i = 1;
	remove_env(&(*e));
	if (e->nb_arg == 2)
	{
		refresh_display(1);
		return ;
	}
	if (e->arg[2])
	{
		e->cmd = e->arg[2];
		arg_handler(&(*e));
		if (exec(&(*e)) < 0)
			refresh_display(2);
	}
}

void		launch_env(t_env *e)
{
	int		i;

	i = 0;
	if (e->arg[1])
	{
		if (ft_strcmp(e->arg[1], "-i") == 0)
		{
			env_i(&(*e));
			return ;
		}
		else
		{
			launch_setenv(&(*e));
			return ;
		}
	}
	while (e->envp[i])
	{
		ft_putstr(e->envp[i]);
		i++;
		ft_putchar('\n');
	}
}

void		launch_setenv(t_env *e)
{
	char	*new_set;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (e->nb_arg < 2)
		launch_env(&(*e));
	else if (e->nb_arg > 3)
	{
		ft_putstr("setenv: Too many arguments.\n");
		return ;
	}
	else if (e->nb_arg == 3 || e->nb_arg == 2)
	{
		new_set = ft_strjoin(e->arg[1], "=");
		while (e->envp[i])
			i++;
		j = add_to_env(new_set, i, &(*e));
		e->envp[j] = NULL;
	}
}
