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

int		get_pos(int *y, int *x)
{
	char buf[30];
	int ret;
	int i;
	int pow;
	char ch;

	buf[0] = 0;
	*y = 0;
	*x = 0;
	write(1, "\e[6n", 4);
	ch = 0;
	for( i = 0, ch = 0; ch != 'R'; i++ )
	{
		ret = read(0, &ch, 1);
		if ( !ret )
		{
			return 1;
		}
		buf[i] = ch;
	}

	if (i < 2)
	{
		ft_printf("i < 2\n");
		return(1);
	}

	for( i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
		*x = *x + ( buf[i] - '0' ) * pow;
	(*x)--;

	for( i-- , pow = 1; buf[i] != '['; i--, pow *= 10)
		*y = *y + ( buf[i] - '0' ) * pow;
	(*y)--;
	return 0;
}

int		move_to(int new_pos)
{
	ft_printf("\e[%d;%dH", new_pos / g_all.term.term_width + 1, new_pos % g_all.term.term_width + 1);
	return (0);
}

int		start_line()
{
	int		x;
	int		y;

	if ((g_all.term.prompt_size = ft_printf("%s %s", get_var("?"), PROMPT)) == -1)
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
