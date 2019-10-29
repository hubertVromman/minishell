/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:32:28 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/29 11:32:30 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *var)
{
	int		i;

	i = -1;
	while (++i < g_all.var_len)
	{
		if (ft_strncmp(var, g_all.var[i], ft_strlen(var)) == 0)
			return (g_all.var[i] + ft_strlen(var) + 1);
	}
	return (NULL);
}

int		get_var_pos(char *var)
{
	int		i;

	i = -1;
	while (++i < g_all.var_len)
	{
		if (ft_strncmp(var, g_all.var[i], ft_strlen(var)) == 0)
			return (i);
	}
	return (-1);
}

int		print_var()
{
	int		i;

	i = -1;
	while (++i < g_all.var_len)
	{
		ft_printf("%s\n", g_all.var[i]);
	}
	return (0);
}
