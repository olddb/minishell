/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 21:35:09 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/15 19:19:01 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void			is_built_in(t_env *e)
{
	e->is_built = 0;
	if (ft_strcmp(e->cmd, "cd") == 0)
		e->is_built = 1;
	else if (ft_strcmp(e->cmd, "setenv") == 0)
		e->is_built = 2;
	else if (ft_strcmp(e->cmd, "unsetenv") == 0)
		e->is_built = 3;
	else if (ft_strcmp(e->cmd, "env") == 0)
		e->is_built = 4;
}

int				cmd_split(t_env *e)
{
	char		**tab;
	int			i;

	i = 0;
	if (!*e->line)
	{
		e->cmd = NULL;
		e->line = NULL;
		e->is_empty = 1;
		return (-1);
	}
	else
	{
		tab = ft_strsplit(e->line, ' ', &e->nb_arg);
		while (tab[i])
		{
			tab[i] = ft_strtrim(tab[i]);
			i++;
		}
		i = 0;
		e->cmd = tab[0];
		e->arg = tab++;
		is_built_in(&(*e));
	}
	return (0);
}

static void		shell_env(t_env *e)
{
	int			i;
	char		*new_sh;

	i = 0;
	while (e->envp[i] && ft_memcmp(e->envp[i], "SHELL=", 5))
		i++;
	if (e->envp[i])
	{
		new_sh = ft_strjoin("SHELL=", getcwd(NULL, 100));
		new_sh = ft_strjoin(new_sh, "/ft_minishell1");
		e->envp[i] = new_sh;
	}
}

void			env_maker(char **envp, t_env *e)
{
	int			i;
	t_make		make;

	i = 0;
	e->envp = envp;
	while (envp[i] && ft_memcmp(envp[i], "PATH=", 5))
		i++;
	if (envp[i])
		e->path = ft_strsplit((envp[i] + 5), ':', &e->nb_path);
	i = 0;
	while (e->envp[i] && ft_memcmp(e->envp[i], "SHLVL=", 5))
		i++;
	if (e->envp[i])
	{
		make.shlvl = ft_atoi(ft_strsub(e->envp[i], 6, ft_strlen(e->envp[i])));
		make.new_shlvl = ft_strjoin("SHLVL=", ft_itoa(make.shlvl + 1));
		e->envp[i] = make.new_shlvl;
	}
	i = 0;
	shell_env(&(*e));
	e->envp_fake = e->envp;
}

void			perm_maker(char *path, t_env *e)
{
	char		*perm;
	struct stat	file_stat;

	perm = ft_strnew(10);
	stat(path, &file_stat);
	perm[0] = ((S_ISDIR(file_stat.st_mode)) ? 'd' : '-');
	perm[1] = ((file_stat.st_mode & S_IRUSR) ? 'r' : '-');
	perm[2] = ((file_stat.st_mode & S_IWUSR) ? 'w' : '-');
	perm[3] = ((file_stat.st_mode & S_IXUSR) ? 'x' : '-');
	perm[4] = ((file_stat.st_mode & S_IRGRP) ? 'r' : '-');
	perm[5] = ((file_stat.st_mode & S_IWGRP) ? 'w' : '-');
	perm[6] = ((file_stat.st_mode & S_IXGRP) ? 'x' : '-');
	perm[7] = ((file_stat.st_mode & S_IROTH) ? 'r' : '-');
	perm[8] = ((file_stat.st_mode & S_IWOTH) ? 'w' : '-');
	perm[9] = ((file_stat.st_mode & S_IXOTH) ? 'x' : '-');
	e->perm = perm;
}
