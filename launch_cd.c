/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/02 14:26:02 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/16 00:23:18 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void			go_to_oldpwd(t_env *e)
{
	char		*way_to_oldpwd;
	int			j;

	j = 0;
	while (e->envp[j] && ft_memcmp(e->envp[j], "OLDPWD=", 7))
		j++;
	if (!e->envp[j])
		return ;
	way_to_oldpwd = ft_strsub(e->envp[j], 7, ft_strlen(e->envp[j]) - 7);
	if (chdir(way_to_oldpwd) < 0)
		return ;
}

char			*go_to_home(t_env *e)
{
	char		*way_to_home;
	int			j;

	j = 0;
	if (e->arg[0][1] == '-')
	{
		go_to_oldpwd(&(*e));
		return (0);
	}
	while (e->envp[j] && ft_memcmp(e->envp[j], "HOME=", 5))
		j++;
	if (!e->envp[j])
		return (0);
	way_to_home = ft_strsub(e->envp[j], 5, ft_strlen(e->envp[j]) - 5);
	if (chdir(way_to_home) < 0)
		return (0);
	return (0);
}

void			launch_cd(t_env *e)
{
	if (!e->arg[1] || e->arg[1][0] == '~' || e->arg[1][0] == '-')
	{
		go_to_home(&(*e));
		return ;
	}
	perm_maker(e->arg[1], &(*e));
	if (e->nb_arg > 2)
	{
		ft_putstr("cd: Too many arguments.\n");
		return ;
	}
	if (e->nb_arg == 1)
		return ;
	if (e->perm[0] != 'd')
	{
		ft_putstr(e->arg[e->nb_arg - 1]);
		ft_putstr(": Not a directory.\n");
	}
	else if (e->perm[1] != 'r')
	{
		ft_putstr(e->arg[e->nb_arg - 1]);
		ft_putstr(": Permission denied.\n");
	}
	if (chdir(e->arg[1]) < 0)
		return ;
}
