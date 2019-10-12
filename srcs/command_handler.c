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

/* Includes necessaires pour la fonction wait() */
#include <sys/types.h>
#include <sys/wait.h>

int		command_handler()
{
	return (0);
}

int		pwd_builtin()
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX) == NULL)
	{
		ft_printf("%s\n%>", buf, 2);
		return (1);
	}
	else
	{
		ft_printf("%s\n", buf);
	}
	return (0);
}

char	*get_env_var(char *var)
{
	int		i;

	i = -1;
	while (g_all.env[++i])
	{
		if (ft_strncmp(var, g_all.env[i], ft_strlen(var)) == 0)
			return (g_all.env[i] + ft_strlen(var) + 1);
	}
	return (NULL);
}

char	*replace_home(char *arg, int *is_to_free)
{
	char	*home_path;

	*is_to_free = 0;
	if (arg[0] != '~')
		return (arg);
	else if (!(home_path = get_env_var("HOME")))
		return (arg);
	else
	{
		*is_to_free = 1;
		return (ft_strjoin(home_path, arg + 1));
	}
}

int		cd_builtin()
{
	char	buf[PATH_MAX];
	char	*arg;
	int		is_to_free;

	if (g_all.command.nb_args > 1)
		return (error("cd: too many arguments", ""));
	if (getcwd(buf, PATH_MAX) == NULL)
		return (error(SHELL_NAME ": ", buf));
	if (g_all.command.nb_args == 0)
		arg = "~";
	else
		arg = g_all.command.structured_args[0];
	if (!(arg = replace_home(arg, &is_to_free)))
		return (-1);
	if (chdir(arg) == -1)
	{
		ft_memcpy(buf, arg, ft_strlen(arg) + 1);
		if (buf[0] != '/')
		{
			ft_memrcpy(buf + 2, buf, ft_strlen(buf) + 1);
			buf[0] = '.';
			buf[1] = '/';
		}
		if (access(buf, F_OK) == -1)
			error("cd: no such file or directory: ", arg);
		else if (access(buf, R_OK) == -1)
			error("cd: permission denied: ", arg);
		else
			error("cd: unknow error: ", arg);
		if (is_to_free)
			free(arg);
		return (-1);
	}
	if (is_to_free)
		free(arg);
	return (0);
}

int		get_nb_args()
{
	int		i;
	int		nb_args;

	i = 0;
	nb_args = 0;
	while (g_all.command.arguments[i])
	{
		while (g_all.command.arguments[i] == ' ')
			i++;
		if (g_all.command.arguments[i])
			nb_args++;
		while (g_all.command.arguments[i] != ' ' && g_all.command.arguments[i] != 0)
			i++;
	}
	return (nb_args);
}

int		parse_arguments()
{
	int		i;
	int		arg_nb;
	int		arg_len;

	g_all.command.nb_args = get_nb_args();
	if (!(g_all.command.structured_args = malloc(sizeof(*g_all.command.structured_args) * (g_all.command.nb_args + 1))))
		return (-1);
	i = 0;
	arg_nb = -1;
	while (g_all.command.arguments[i])
	{
		while (g_all.command.arguments[i] == ' ')
			i++;
		arg_nb++;
		if ((arg_len = ft_indexof(g_all.command.arguments + i, ' ')) == -1)
			arg_len = ft_strlen(g_all.command.arguments);
		if (!(g_all.command.structured_args[arg_nb] = ft_strsub(g_all.command.arguments, i, arg_len)))
			return (-1);
		i += arg_len;
	}
	return (0);
}

int		builtin_handler()
{
	if (ft_strcmp(g_all.command.command, "echo") == 0)
		;
	else if (ft_strcmp(g_all.command.command, "cd") == 0)
		return (cd_builtin());
	else if (ft_strcmp(g_all.command.command, "setenv") == 0)
		;
	else if (ft_strcmp(g_all.command.command, "unsetenv") == 0)
		;
	else if (ft_strcmp(g_all.command.command, "env") == 0)
		;
	else if (ft_strcmp(g_all.command.command, "exit") == 0)
		;
	else if (ft_strcmp(g_all.command.command, "pwd") == 0)
		return (pwd_builtin());
	else
		return (1);
	return (0);
}

int		dispatcher()
{
	int		ret;
	int		status;
	char	*arg[3];

	g_all.command.command = g_all.line;
	if ((ret = ft_indexof(g_all.line, ' ')) != -1)
	{
		g_all.line[ret] = 0;
		g_all.command.arguments = g_all.line + ret + 1;
	}
	else
		g_all.command.arguments = "";

	if (parse_arguments() != 0)
		return (-1);

	if ((ret = builtin_handler()) != 0)
		return (ret);
	else
		return (command_handler());
	arg[0] = "ls";
	arg[1] = "-C";
	arg[2] = NULL;

	if ((g_all.command.child_pid = fork()) == -1)
	{
		ft_printf("fork failed\n");
		return -1;
	}
	else if (g_all.command.child_pid == 0)
	{
		if (execve("/bin/ls", (char **)arg, g_all.env) == -1)
			ft_printf("Execution failed\n");
		return 1;
	}
	else
		wait(&status);
	return 0;
}
