/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:40:22 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/21 11:40:25 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_history(int new_pos)
{
	g_all.history.pos_in_history = new_pos;
	if (g_all.history.pos_in_history < 0)
		g_all.history.pos_in_history = 0;
	else if (g_all.history.pos_in_history > g_all.history.size)
		g_all.history.pos_in_history = g_all.history.size;
	return (g_all.history.data[g_all.history.pos_in_history]);
}

int		check_move_history(char *compare, int new_history_pos)
{
	if (
	!ft_strncmp(g_all.history.base, compare, g_all.history.cursor_pos_in_base)
		&& (ft_strcmp(g_all.history.base, compare) != 0
			|| g_all.history.base_pos == new_history_pos)
		&& ft_strcmp(g_all.current_line, compare) != 0)
	{
		move_to(g_all.term.line_start);
		ft_printf("%/*c", ft_strlen(g_all.current_line), ' ');
		if (g_all.current_line != g_all.line)
			free(g_all.current_line);
		if (new_history_pos == g_all.history.size)
			g_all.current_line = g_all.line;
		else
			g_all.current_line = ft_strdup(get_history(new_history_pos));
		move_to(g_all.term.line_start);
		ft_printf("%s", g_all.current_line);
		g_all.line_size = ft_strlen(g_all.current_line);
		g_all.line_malloc_size = g_all.line_size;
		g_all.term.cursor_pos = g_all.term.line_start + g_all.line_size;
		g_all.cursor_pos_in_line = g_all.line_size;
		g_all.history.pos_in_history = new_history_pos;
		return (1);
	}
	return (0);
}

int		get_previous_pos_of(int direction)
{
	int		new_history_pos;
	char	*compare;

	new_history_pos = g_all.history.pos_in_history;
	if (g_all.history.base == NULL)
	{
		if (!(g_all.history.base = ft_strdup(g_all.current_line)))
			exit_func(MERROR);
		g_all.history.cursor_pos_in_base = g_all.cursor_pos_in_line;
		g_all.history.base_pos = g_all.history.pos_in_history;
	}
	while (1)
	{
		new_history_pos += direction;
		if (new_history_pos > g_all.history.size || new_history_pos < 0)
			return (1);
		if (new_history_pos == g_all.history.size)
			compare = g_all.line;
		else
			compare = g_all.history.data[new_history_pos];
		if (check_move_history(compare, new_history_pos))
			return (0);
	}
	return (1);
}
