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

int		getch(void)
{
	char c;

	read(0, &c, 1);
	return(c);
}

int		realloc_line()
{
	char	*tmp;

	tmp = g_all.line;
	if (!(g_all.line = malloc(g_all.line_size + REALLOC_SIZE + 1)))
		exit(0);
	memcpy(g_all.line, tmp, g_all.line_size);
	g_all.line[g_all.line_size] = 0;
	return (0);
}

int		append_to_line(char ch, int pos)
{
	if (g_all.line_size == 0)
		if (!(g_all.line = malloc(REALLOC_SIZE + 1)))
			exit(0);
	++g_all.line_size;
	if ((g_all.line_size) % REALLOC_SIZE == 0)
		realloc_line();
	ft_memrcpy(g_all.line + pos + 1, g_all.line + pos, g_all.line_size - pos + 1);
	g_all.line[pos] = ch;
	return (0);
}

int		deal_with_this(char ch)
{
	if (ch == 4)
	{
		if (!g_all.line_size)
			exit(0);
	}
	else if (ch == '\e')
	{
		ch = getch();
		if (ch == '[')
		{
			ch = getch();
			if (ch == 'A')
			{
				ft_printf("fleche haut");
			}
			else if (ch == 'B')
			{
				ft_printf("fleche bas");
			}
			else if (ch == 'C')
			{
				if (g_all.cursor_pos_in_line < g_all.line_size)
				{
					g_all.term.cursor_pos++;
					g_all.cursor_pos_in_line++;
					move_to(g_all.term.cursor_pos);
				}
			}
			else if (ch == 'D')
			{
				if (g_all.cursor_pos_in_line)
				{
					g_all.term.cursor_pos--;
					g_all.cursor_pos_in_line--;
					move_to(g_all.term.cursor_pos);
				}
			}
		}
	}
	else if (ch == 127)
	{
		if (g_all.cursor_pos_in_line)
		{
			g_all.line_size--;
			g_all.term.cursor_pos--;
			g_all.cursor_pos_in_line--;
			ft_memcpy(g_all.line + g_all.cursor_pos_in_line, g_all.line + g_all.cursor_pos_in_line + 1, g_all.line_size - g_all.cursor_pos_in_line + 1);
			move_to(g_all.term.cursor_pos);
			ft_printf("%s ", g_all.line + g_all.cursor_pos_in_line);
			move_to(g_all.term.cursor_pos);
		}
	}
	else if (ch != '\n')
	{
		append_to_line(ch, g_all.cursor_pos_in_line);
		ft_printf("%s", g_all.line + g_all.cursor_pos_in_line);
		g_all.term.cursor_pos++;
		g_all.cursor_pos_in_line++;
		move_to(g_all.term.cursor_pos);
	}
	return (0);
}
