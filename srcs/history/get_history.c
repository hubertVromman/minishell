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

int		get_previous_pos_of(int direction)
{
	int		new_cursor_pos;
	char	*compare;

	new_cursor_pos = g_all.history.pos_in_history;
	if (g_all.history.base == NULL)
	{
		if (!(g_all.history.base = ft_strdup(g_all.current_line)))
			exit_func(MERROR);
		g_all.history.cursor_pos_in_base = g_all.cursor_pos_in_line;
		g_all.history.base_pos = g_all.history.pos_in_history;
	}
	while (1)
	{
		new_cursor_pos += direction;
		if (new_cursor_pos > g_all.history.size || new_cursor_pos < 0)
			return (1);
		if (new_cursor_pos == g_all.history.size)
			compare = g_all.line;
		else
			compare = g_all.history.data[new_cursor_pos];
		// ft_printf("--------------------------------------------------------\n%>", g_all.history.write_fd);
		// ft_printf("line <%s>\n%>", g_all.line, g_all.history.write_fd);
		// ft_printf("current_line <%s>\n%>", g_all.current_line, g_all.history.write_fd);
		// ft_printf("base <%s>\n%>", g_all.history.base, g_all.history.write_fd);
		// ft_printf("compare <%s>\n%>", compare, g_all.history.write_fd);
		// ft_printf("base_pos <%d>\n%>", g_all.history.base_pos, g_all.history.write_fd);
		// ft_printf("new_cursor_pos <%d>\n%>", new_cursor_pos, g_all.history.write_fd);
		// ft_printf("pos_in_history <%d>\n%>", g_all.history.pos_in_history, g_all.history.write_fd);
		// ft_printf("history size <%d>\n%>", g_all.history.size, g_all.history.write_fd);
		// ft_printf("--------------------------------------------------------\n%>", g_all.history.write_fd);
		if (ft_strncmp(g_all.history.base, compare, g_all.history.cursor_pos_in_base) == 0
			&& (ft_strcmp(g_all.history.base, compare) != 0 || g_all.history.base_pos == new_cursor_pos)
			&& ft_strcmp(g_all.current_line, compare) != 0)
		{
			move_to(g_all.term.line_start);
			ft_printf("%/*c", ft_strlen(g_all.current_line), ' ');
			// leak
			if (g_all.current_line != g_all.line)
				free(g_all.current_line);
			if (new_cursor_pos == g_all.history.size)
				g_all.current_line = g_all.line;
			else
				g_all.current_line = ft_strdup(get_history(new_cursor_pos));
			move_to(g_all.term.line_start);
			ft_printf("%s", g_all.current_line);
			g_all.line_size = ft_strlen(g_all.current_line);
			g_all.line_malloc_size = g_all.line_size;
			g_all.term.cursor_pos = g_all.term.line_start + g_all.line_size;
			g_all.cursor_pos_in_line = g_all.line_size;
			g_all.history.pos_in_history = new_cursor_pos;
			return (0);
		}
	}
	return (1);
}
