/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:58:08 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/14 14:58:10 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int		builtin_dispatcher()
{
	if (ft_strcmp(g_all.command.command, "echo") == 0)
		echo_builtin();
	else if (ft_strcmp(g_all.command.command, "cd") == 0)
		cd_builtin() && (g_all.command.exit_status = 1);
	else if (ft_strcmp(g_all.command.command, "setenv") == 0)
		setenv_builtin();
	else if (ft_strcmp(g_all.command.command, "unsetenv") == 0)
		unsetenv_builtin();
	else if (ft_strcmp(g_all.command.command, "env") == 0)
		env_builtin();
	else if (ft_strcmp(g_all.command.command, "exit") == 0)
		exit_builtin();
	// else if (ft_strcmp(g_all.command.command, "pwd") == 0)
	// 	pwd_builtin();
	else
		return (-1);
	return (0);
}
