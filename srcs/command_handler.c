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

int		search_path()
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
		if (g_all.command.command_expanded[ret - 1] != '/')
		{
			g_all.command.command_expanded[ret] = '/';
			slash = 1;
		}
		ft_memcpy(g_all.command.command_expanded + ret + slash, g_all.command.command, ft_strlen(g_all.command.command) + 1);
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

int		command_handler()
{
	int		status;

	if (g_all.command.command[0] == '/' || g_all.command.command[0] == '.')
		ft_memcpy(g_all.command.command_expanded, g_all.command.command, ft_strlen(g_all.command.command));
	else if (search_path() == -1)
	{
		error("minishell: command not found: ", g_all.command.command);
		g_all.command.exit_status = 127;
		return (-1);
	}
	if (access(g_all.command.command_expanded, X_OK) == -1)
	{
		g_all.command.exit_status = 126;
		error("minishell: permission denied: ", g_all.command.command);
		return (-1);
	}
	else
	{
		if ((g_all.command.child_pid = fork()) == -1)
		{
			ft_printf("fork failed\n");
			return -1;
		}
		else if (g_all.command.child_pid == 0)
		{
			if (execve(g_all.command.command_expanded, g_all.command.structured_args, g_all.env) == -1)
		ft_printf("Execution failed\n");
		}
		else
		{
			waitpid(g_all.command.child_pid, &status, 0);
			if (!g_all.signal_sent)
				g_all.command.exit_status = WEXITSTATUS(status);
		}
	}
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

	g_all.command.nb_args = get_nb_args() + 1;
	if (!(g_all.command.structured_args = malloc(sizeof(char*) * (g_all.command.nb_args + 1))))
		exit_func(MERROR);
	i = 0;
	arg_nb = 0;
	g_all.command.structured_args[0] = g_all.command.command;
	while (g_all.command.arguments[i])
	{
		while (g_all.command.arguments[i] == ' ')
			i++;
		arg_nb++;
		if ((arg_len = ft_indexof(g_all.command.arguments + i, ' ')) == -1)
			arg_len = ft_strlen(g_all.command.arguments) - i;
		if (!(g_all.command.structured_args[arg_nb] = ft_strsub(g_all.command.arguments, i, arg_len)))
			exit_func(MERROR);
		i += arg_len;
	}
	g_all.command.structured_args[arg_nb + 1] = NULL;
	return (0);
}

char	*replace_dollar(char *line, int dollar_pos, int end)
{
	char	*replacement;
	char	*to_replace;
	int		final_len;
	char	*final_line;
	int		replacement_len;

	if (!(to_replace = ft_strsub(line, dollar_pos, end - dollar_pos)))
		exit_func(MERROR);
	if (!(replacement = get_env_var(to_replace + 1)))
		replacement = "";
	free(to_replace);
	replacement_len = ft_strlen(replacement);
	final_len = dollar_pos + replacement_len + ft_strlen(line) - end;
	if (!(final_line = malloc(final_len)))
		exit_func(MERROR);
	ft_memcpy(final_line, line, dollar_pos);
	ft_memcpy(final_line + dollar_pos, replacement, replacement_len);
	ft_memcpy(final_line + dollar_pos + replacement_len, line + end, ft_strlen(line) - end + 1);
	return (final_line);
}

char	*search_dollar(char *line)
{
	int		dollar_pos;
	char	*tmp;
	int		end;

	while ((dollar_pos = ft_indexof(line, '$')) != -1)
	{
		end = dollar_pos + 1;
		while (ft_isalnum(line[end]))
			end++;
		if (end != dollar_pos + 1)
		{
			tmp = replace_dollar(line, dollar_pos, end);
			end = dollar_pos + 1;
			free(line);
			line = tmp;
		}
	}
	return (line);
}

int		end_dispatcher(int coma_pos)
{
	ft_free_tab((void***)&(g_all.command.structured_args));
	if (coma_pos != -1)
	{
		g_all.pos_in_command += coma_pos + 1;
		if (!(g_all.current_command_line = ft_strdup(g_all.current_line + g_all.pos_in_command)))
			exit_func(MERROR);
		dispatcher();
	}
	return (0);
}

int		dispatcher()
{
	int		ret;
	int		i;
	int		coma_pos;

	if ((coma_pos = ft_indexof(g_all.current_command_line, ';')) != -1)
		g_all.current_command_line[coma_pos] = 0;
	i = -1;
	while (g_all.current_command_line[++i] == ' ')
		;
	if (g_all.current_command_line[i] && coma_pos == -1)
		add_to_history(g_all.current_line);
	g_all.current_command_line = search_dollar(g_all.current_command_line);
	g_all.command.command = g_all.current_command_line + i;
	if ((ret = ft_indexof(g_all.command.command, ' ')) != -1)
	{
		g_all.command.command[ret] = 0;
		g_all.command.arguments = g_all.command.command + ret + 1;
	}
	else
		g_all.command.arguments = "";

	if (!g_all.command.command[0])
		return (end_dispatcher(coma_pos));
	g_all.command.exit_status = 0;

	parse_arguments();

	if (builtin_dispatcher() == -1)
		command_handler();
	return (end_dispatcher(coma_pos));
}
