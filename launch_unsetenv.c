/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_unsetenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 14:54:38 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/16 14:43:52 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void		remove_to_env(char *str, int i, t_env *e)
{
	char	**new_env;
	int		j;
	int		p;

	j = 0;
	p = 0;
	new_env = (char **)malloc(sizeof(new_env) * i + 1);
	str = ft_strjoin(str, "=");
	while (j < i)
	{
		if (ft_memcmp(e->envp[j], str, ft_strlen(str)) == 0)
		{
			p = 1;
			j++;
		}
		if (e->envp[j])
		{
			new_env[j - p] = (char *)malloc(sizeof(new_env) *
					(ft_strlen(e->envp[j]) + 1));
			ft_memcpy(new_env[j - p], e->envp[j], ft_strlen(e->envp[j]) + 1);
		}
		j++;
	}
	new_env[j - p] = NULL;
	e->envp = new_env;
}

void		launch_unsetenv(t_env *e)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (e->nb_arg < 2)
	{
		ft_putstr("unsetenv: Too few arguments.\n");
		return ;
	}
	while (e->envp[i])
		i++;
	while (e->arg[j])
	{
		remove_to_env(e->arg[j], i, &(*e));
		j++;
	}
}

void		remove_env(t_env *e)
{
	char	**new_env;

	new_env = (char **)malloc(sizeof(new_env) * 26);
	e->is_save = 1;
	e->envp_fake = new_env;
}
