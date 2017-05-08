/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/14 17:34:45 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/16 15:03:18 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int					ex_handler(t_env *e)
{
	char			*path;
	char			*path_save;
	int				i;

	i = 0;
	while (e->cmd[i])
	{
		if (e->cmd[i] == '/')
			if (execve(e->cmd, e->arg, e->envp_fake) == -1)
				return (-1);
		i++;
	}
	path = ft_strjoin("/\0", e->cmd);
	path_save = path;
	i = 0;
	while (i < e->nb_path)
	{
		path = ft_strjoin(e->path[i], path);
		if (execve(path, e->arg, e->envp_fake) != -1)
			return (1);
		i++;
		path = path_save;
	}
	print_error(e->cmd);
	return (-1);
}

int					exec(t_env *e)
{
	pid_t			father;

	father = fork();
	if (father > 0)
		wait(0);
	if (father == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (ex_handler(&(*e)) == 1)
			return (1);
		else
		{
			exit(0);
			return (-1);
		}
	}
	refresh_display(1);
	return (0);
}

int					run(t_env *e)
{
	get_next_line(0, &e->line);
	tab_remove(&(*e));
	if (e->is_save == 1)
		e->envp_fake = e->envp;
	if (line_check(&(*e)) == -1)
	{
		refresh_display(2);
		return (0);
	}
	if (cmd_split(&(*e)) == -1)
		return (0);
	if (ft_strcmp(e->cmd, "exit") == 0)
	{
		ft_putstr("exit\n");
		return (-1);
	}
	if (e->is_built != 0)
		launch_built(&(*e));
	else
		return (exec(&(*e)));
	if (e->is_env_i != 1)
		refresh_display(1);
	e->is_env_i = 0;
	return (0);
}
