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
	char buf[30]={0};
	int ret, i, pow;
	char ch;

	*y = 0; *x = 0;

	write(1, "\e[6n", 4);

	for( i = 0, ch = 0; ch != 'R'; i++ )
	{
		ret = read(0, &ch, 1);
		if ( !ret )
		{
			// fprintf(stderr, "getpos: error reading response!\n");
			return 1;
		}
		buf[i] = ch;
		// ft_printf("buf[%d]: \t%c \t%d\n", i, ch, ch);
	}

	if (i < 2)
	{
		ft_printf("i < 2\n");
		return(1);
	}

	for( i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
		*x = *x + ( buf[i] - '0' ) * pow;

	for( i-- , pow = 1; buf[i] != '['; i--, pow *= 10)
		*y = *y + ( buf[i] - '0' ) * pow;
	return 0;
}

int		move_to(int new_pos)
{
	ft_printf("\e[%d;%dH", new_pos / g_all.term.term_width, new_pos % g_all.term.term_width);
	return (0);
}

int		start_line()
{
	int		x;
	int		y;

	g_all.line_size = 0;
	ft_printf("%s", PROMPT);
	get_pos(&y, &x);
	g_all.term.line_start = y * g_all.term.term_width + x;
	g_all.term.cursor_pos = g_all.term.line_start;
	g_all.cursor_pos_in_line = 0;
	return (0);
}
