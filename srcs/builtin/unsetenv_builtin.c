/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:05:06 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/14 15:05:07 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		unsetenv_builtin(void)
{
	int		i;
	int		pos;

	if (g_all.command.nb_args < 2)
		return (error("unsetenv: Too few arguments.", ""));
	i = 0;
	while (++i < g_all.command.nb_args)
	{
		if ((pos = get_env_pos(g_all.command.structured_args[i])) != -1)
			delete_env_var(pos);
	}
	return (0);
}
