/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 11:21:51 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/12 11:21:53 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_pos_reader(char *buf, int *x, int *y, int i)
{
	int		pow;

	i -= 2;
	pow = 1;
	while (buf[i] != ';')
	{
		*x = *x + (buf[i] - '0') * pow;
		i--;
		pow *= 10;
	}
	(*x)--;
	i--;
	pow = 1;
	while (buf[i] != '[')
	{
		*y = *y + (buf[i] - '0') * pow;
		i--;
		pow *= 10;
	}
	(*y)--;
	return (0);
}

int		get_pos(int *y, int *x)
{
	char	buf[30];
	int		i;
	char	ch;

	buf[0] = 0;
	*y = 0;
	*x = 0;
	write(1, "\e[6n", 4);
	ch = 0;
	i = 0;
	while (ch != 'R')
	{
		if (!read(0, buf + i, 1))
			return (1);
		ch = buf[i];
		i++;
	}
	if (i < 2)
		return (1);
	return (get_pos_reader(buf, x, y, i));
}

int		move_to(int new_pos)
{
	ft_printf(MOVE_TO, new_pos / g_all.term.term_width + 1,
		new_pos % g_all.term.term_width + 1);
	return (0);
}

int		start_line(void)
{
	int		x;
	int		y;

	if ((g_all.term.prompt_size =
		ft_printf("%s %s", get_var("?"), PROMPT)) == -1)
		g_all.term.prompt_size = 0;
	get_pos(&y, &x);
	g_all.term.line_start = y * g_all.term.term_width + x;
	g_all.term.cursor_pos = g_all.term.line_start;
	g_all.cursor_pos_in_line = 0;
	g_all.history.pos_in_history = g_all.history.size;
	g_all.line_malloc_size = REALLOC_SIZE;
	if (!(g_all.line = ft_strnew(REALLOC_SIZE)))
		exit_func(MERROR);
	g_all.current_line = g_all.line;
	return (0);
}
