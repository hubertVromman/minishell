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
