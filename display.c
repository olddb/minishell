/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 20:49:09 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/16 14:18:58 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell1.h"

int			refresh_display(int color)
{
	if (color == 1)
		ft_putstr("\033[032m~(__^> \033[0m");
	if (color == 2)
		ft_putstr("\033[031m~(__^> \033[0m");
	return (1);
}

void		print_error(char *cmd)
{
	ft_putstr(cmd);
	ft_putstr(": Command not found.\n");
}
