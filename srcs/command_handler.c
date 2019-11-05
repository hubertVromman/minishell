/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 11:38:36 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/12 11:38:37 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		search_path(void)
{
	char	*path;
	int		i;
	int		ret;
	int		slash;

	if (!(path = ft_strdup(get_env_var("PATH"))))
		return (-1);
	i = 0;
	while ((ret = ft_indexof(path + i, ':')) != -1)
	{
		slash = 0;
		ft_memcpy(g_all.command.command_expanded, path + i, ret);
		if (g_all.command.command_expanded[ret - 1] != '/' && (slash = 1))
			g_all.command.command_expanded[ret] = '/';
		ft_memcpy(g_all.command.command_expanded + ret + slash,
			g_all.command.command, ft_strlen(g_all.command.command) + 1);
		if (access(g_all.command.command_expanded, F_OK) == 0)
		{
			free(path);
			return (0);
		}
		i += ret + 1;
	}
	free(path);
	return (-1);
}

int		fork_creation(void)
{
	int		status;

	if ((g_all.command.child_pid = fork()) == -1)
	{
		ft_printf("fork failed\n");
		return (-1);
	}
	else if (g_all.command.child_pid == 0)
	{
		if (execve(g_all.command.command_expanded,
			g_all.command.structured_args, g_all.env) == -1)
			ft_printf("Execution failed\n");
	}
	else
	{
		waitpid(g_all.command.child_pid, &status, 0);
		if (!g_all.signal_sent)
			g_all.command.exit_status = WEXITSTATUS(status);
	}
	return (0);
}

int		command_handler(void)
{
	if (g_all.command.command[0] == '/' || g_all.command.command[0] == '.')
		ft_memcpy(g_all.command.command_expanded, g_all.command.command,
			ft_strlen(g_all.command.command) + 1);
	else if (search_path() == -1)
	{
		error("minishell: command not found: ", g_all.command.command);
		g_all.command.exit_status = 127;
		return (-1);
	}
	if (access(g_all.command.command_expanded, X_OK) == -1)
	{
		g_all.command.exit_status = 126;
		error("minishell: permission denied: ", g_all.command.command_expanded);
		return (-1);
	}
	else
	{
		fork_creation();
	}
	return (0);
}
