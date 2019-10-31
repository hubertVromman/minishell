/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:35:39 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/14 14:35:42 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		get_error(char *buf, char *arg, int is_to_free)
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

int		cd_builtin(void)
{
	char	buf[PATH_MAX];
	char	*arg;
	int		is_to_free;

	if (g_all.command.nb_args > 2)
		return (error("cd: too many arguments", ""));
	if (getcwd(buf, PATH_MAX) == NULL)
		return (error(SHELL_NAME ": ", buf));
	if (g_all.command.nb_args == 1)
		arg = "~";
	else
		arg = g_all.command.structured_args[1];
	if (!(arg = replace_home(arg, &is_to_free)))
		return (-1);
	if (chdir(arg) == -1)
		return (get_error(buf, arg, is_to_free));
	if (is_to_free)
		free(arg);
	return (0);
}
