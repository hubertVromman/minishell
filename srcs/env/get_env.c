/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:45:50 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/14 14:45:52 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_var(char *var)
{
	int		i;

	i = -1;
	while (++i < g_all.env_len)
	{
		if (ft_strncmp(var, g_all.env[i], ft_strlen(var)) == 0)
			return (g_all.env[i] + ft_strlen(var) + 1);
	}
	return (NULL);
}

int		get_env_pos(char *var)
{
	int		i;

	i = -1;
	while (++i < g_all.env_len)
	{
		if (ft_strncmp(var, g_all.env[i], ft_strlen(var)) == 0)
			return (i);
	}
	return (-1);
}

int		print_env(void)
{
	int		i;

	i = -1;
	while (++i < g_all.env_len)
	{
		ft_printf("%s\n", g_all.env[i]);
	}
	return (0);
}
