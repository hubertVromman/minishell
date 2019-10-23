/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:03:52 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/14 15:04:05 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo_builtin()
{
	int		i;

	i = 0;
	while (++i < g_all.command.nb_args)
	{
		if (i != 1)
			ft_printf(" ");
		ft_printf("%s", g_all.command.structured_args[i]);
	}
	ft_printf("\n");
	return (0);
}
