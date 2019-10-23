/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:04:56 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/14 15:05:03 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		setenv_builtin()
{
	int		pos;
	char	*value;

	if (g_all.command.nb_args < 2)
	{
		print_env();
		return (0);
	}
	else if (g_all.command.nb_args == 2)
		value = "";
	else
		value = g_all.command.structured_args[2];
	if ((pos = get_env_pos(g_all.command.structured_args[1])) != -1)
		modify_env_var(pos, g_all.command.structured_args[1], value);
	else
		add_env_var(g_all.command.structured_args[1], value);
	return (0);
}
