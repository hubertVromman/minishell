/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 11:22:01 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/12 11:22:03 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		getch_killable(void)
{
	char	c;
	int		sleep_time;
	int		ret;
	int		flags;

	flags = fcntl(0, F_GETFL);
	fcntl(0, F_SETFL, O_NONBLOCK);
	sleep_time = 10 * 1000;
	while (1)
	{
		ret = read(0, &c, 1);
		usleep(sleep_time);
		if (ret == 1)
			break ;
		else if (g_all.signal_sent)
		{
			c = '\n';
			break ;
		}
	}
	fcntl(0, F_SETFL, flags);
	return (c);
}

int		realloc_line(void)
{
	char	*tmp;

	if (g_all.current_line == g_all.line)
	{
		if (!(g_all.line = malloc(g_all.line_size + REALLOC_SIZE + 1)))
			exit_func(MERROR);
		ft_memcpy(g_all.line, g_all.current_line, g_all.line_size);
		g_all.line[g_all.line_size] = 0;
		free(g_all.current_line);
		g_all.current_line = g_all.line;
	}
	else
	{
		tmp = g_all.current_line;
		if (!(g_all.current_line = malloc(g_all.line_size + REALLOC_SIZE + 1)))
			exit_func(MERROR);
		ft_memcpy(g_all.current_line, tmp, g_all.line_size);
		g_all.current_line[g_all.line_size] = 0;
		free(tmp);
	}
	g_all.line_malloc_size = g_all.line_size + REALLOC_SIZE;
	return (0);
}

int		append_to_line(char ch, int pos)
{
	++g_all.line_size;
	if (g_all.line_malloc_size + 1 == g_all.line_size)
	{
		realloc_line();
	}
	ft_memrcpy(g_all.current_line + pos + 1, g_all.current_line + pos,
		g_all.line_size - pos);
	g_all.current_line[pos] = ch;
	return (0);
}

int		get_escape(int *free_base)
{
	char	ch;

	if ((ch = getch_killable()) != '[')
		return (deal_with_this(ch));
	ch = getch_killable();
	if (ch == 'A' || ch == 'B')
	{
		get_previous_pos_of(ch == 'A' ? -1 : 1);
		*free_base = 0;
	}
	else if (ch == 'C' && g_all.cursor_pos_in_line < g_all.line_size)
	{
		g_all.term.cursor_pos++;
		g_all.cursor_pos_in_line++;
		move_to(g_all.term.cursor_pos);
	}
	else if (ch == 'D' && g_all.cursor_pos_in_line)
	{
		g_all.term.cursor_pos--;
		g_all.cursor_pos_in_line--;
		move_to(g_all.term.cursor_pos);
	}
	else if (ch != 'C' && ch != 'D')
		deal_with_this(ch);
	return (0);
}

int		add_character(char ch)
{
	append_to_line(ch, g_all.cursor_pos_in_line);
	ft_printf("%s", g_all.current_line + g_all.cursor_pos_in_line);
	g_all.term.cursor_pos++;
	g_all.cursor_pos_in_line++;
	if (g_all.term.term_height <=
		g_all.term.cursor_pos / g_all.term.term_width + 1 &&
		(g_all.line_size + g_all.term.prompt_size) % g_all.term.term_width == 0)
	{
		ft_printf("\n");
		g_all.term.cursor_pos -= g_all.term.term_width;
	}
	move_to(g_all.term.cursor_pos);
	return (0);
}

int		back_space(void)
{
	if (g_all.cursor_pos_in_line)
	{
		g_all.line_size--;
		g_all.term.cursor_pos--;
		g_all.cursor_pos_in_line--;
		ft_memcpy(g_all.current_line + g_all.cursor_pos_in_line,
			g_all.current_line + g_all.cursor_pos_in_line + 1,
			g_all.line_size - g_all.cursor_pos_in_line + 1);
		move_to(g_all.term.cursor_pos);
		ft_printf("%s ", g_all.current_line + g_all.cursor_pos_in_line);
		move_to(g_all.term.cursor_pos);
	}
	return (0);
}

int		deal_with_this(char ch)
{
	int		free_base;

	free_base = 1;
	if (ch == 4)
	{
		if (!g_all.line_size)
		{
			ft_printf("\n");
			exit_no_error(g_all.command.exit_status);
		}
	}
	else if (ch == '\e')
		get_escape(&free_base);
	else if (ch == 127)
		back_space();
	else
		add_character(ch);
	if (free_base)
		ft_strdel(&g_all.history.base);
	return (0);
}
