/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/26 17:48:54 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/16 14:17:56 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL1_H
# define FT_MINISHELL1_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft/libft.h"

typedef struct		s_env{
	char			**envp;
	char			**path;
	int				nb_path;
	int				nb_arg;
	int				is_built;
	int				exit;
	char			*line;
	char			*cmd;
	char			**arg;
	char			**envp_fake;
	int				is_save;
	int				is_empty;
	int				is_env_i;
	char			*perm;
}					t_env;

typedef struct		s_make{
	char			*new_shlvl;
	char			*new_sh;
	int				i;
	int				shlvl;
}					t_make;

int					ex_handler(t_env *e);
void				launch_built(t_env *e);
int					line_check(t_env *e);
int					run(t_env *e);
void				tab_remove(t_env *e);

void				print_error(char *cmd);
int					refresh_display(int color);

void				perm_maker(char *path, t_env *e);
char				*get_user(t_env *e);
int					get_str(t_env *e, char **pwd);
char				*get_home(char *pwd, char *home);
char				*go_to_home(t_env *e);
void				launch_cd(t_env *e);

int					add_to_env(char *str, int i, t_env *e);
void				remove_env(t_env *e);
void				launch_env(t_env *e);
void				launch_setenv(t_env *e);

void				remove_to_env(char *str, int i, t_env *e);
void				launch_unsetenv(t_env *e);

int					cmd_split(t_env *e);
void				is_built_in(t_env *e);
void				env_maker(char **envp, t_env *e);

int					exec(t_env *e);

int					get_next_line(int const fd, char **line);

#endif
