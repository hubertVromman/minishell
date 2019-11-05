/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:24:15 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/31 15:24:17 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		end_dispatcher(int coma_pos)
{
	int		real_coma_pos;

	ft_free_tab((void***)&(g_all.command.structured_args));
	if (coma_pos != -1)
	{
		real_coma_pos = ft_indexof(g_all.current_line + g_all.pos_in_command, ';');
		g_all.pos_in_command += real_coma_pos + 1;
		if (!(g_all.current_command_line =
			ft_strdup(g_all.current_line + g_all.pos_in_command)))
			exit_func(MERROR);
		line_parser();
	}
	return (0);
}

int		line_parser(void)
{
	int		ret;
	int		i;
	int		coma_pos;

	g_all.current_command_line = search_dollar(g_all.current_command_line);
	if ((coma_pos = ft_indexof(g_all.current_command_line, ';')) != -1)
		g_all.current_command_line[coma_pos] = 0;
	i = -1;
	while (g_all.current_command_line[++i] == ' ')
		;
	g_all.command.command = g_all.current_command_line + i;
	if ((ret = ft_indexof(g_all.command.command, ' ')) != -1
		&& (g_all.command.arguments = g_all.command.command + ret + 1))
		g_all.command.command[ret] = 0;
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
