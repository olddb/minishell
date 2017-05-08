/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpailhe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/04 18:55:36 by vpailhe           #+#    #+#             */
/*   Updated: 2015/03/05 16:53:49 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrd(const char *str)
{
	int		i;

	i = 0;
	ft_putchar('\n');
	ft_putstr("         =>");
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
	ft_putstr("<=");
	ft_putchar('\n');
	ft_putchar('\n');
}
