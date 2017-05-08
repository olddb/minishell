/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 12:01:51 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/16 15:03:03 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

void				tab_remove(t_env *e)
{
	int				i;
	int				j;
	char			*str;

	i = 0;
	j = 0;
	e->line = ft_strtrim(e->line);
	str = ft_strnew(ft_strlen(e->line) + 1);
	while (e->line[i] != '\0')
	{
		if (e->line[i] != '	')
		{
			str[j] = e->line[i];
			j++;
		}
		i++;
	}
	e->line = str;
}

void				launch_built(t_env *e)
{
	if (e->is_built == 1)
		launch_cd(&(*e));
	else if (e->is_built == 2)
		launch_setenv(&(*e));
	else if (e->is_built == 3)
		launch_unsetenv(&(*e));
	else if (e->is_built == 4)
		launch_env(&(*e));
}

int					line_check(t_env *e)
{
	int				i;

	i = 0;
	e->line = ft_strtrim(e->line);
	if (ft_strcmp(e->line, "") == 0)
		return (-1);
	if (!*e->line)
		return (-1);
	while (e->line[i] != '\0')
	{
		if (ft_isascii(e->line[i]) == 1)
			return (1);
		i++;
	}
	return (-1);
}

int					main(int argc, char **argv, char **envp)
{
	static t_env	e;

	if (!*envp)
		return (0);
	argc += 42;
	argv += 42;
	env_maker(envp, &e);
	refresh_display(1);
	signal(SIGINT, SIG_IGN);
	while (42)
	{
		if (run(&e) < 0)
			exit(0);
	}
	return (0);
}
