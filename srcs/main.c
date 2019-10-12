/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:33:34 by hvromman          #+#    #+#             */
/*   Updated: 2019/06/20 15:33:35 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init(char **env)
{
	struct termios	org_opts;
	struct ttysize	ts;
	int				res;

	ft_bzero(&g_all, sizeof(g_all));
	g_all.env = env;
	ioctl(0, TIOCGSIZE, &ts);
	g_all.term.term_width = ts.ts_cols;
	g_all.term.term_height = ts.ts_lines;
	res = tcgetattr(0, &org_opts);
	ft_printf("res %d width %d height %d\n", res, g_all.term.term_width, g_all.term.term_height);
	org_opts.c_lflag = (ISIG | OFDEL | IEXTEN) & ~(ICANON); // not sure for ofdel
	tcsetattr(0, TCSANOW, &org_opts);
	signal(SIGWINCH, &sig_winch);
	start_line();
	return (0);
}

int		main(int ac, char **av, char **env)
{
	init(env);
	(void)ac;
	(void)av;
	char	ch;

	while ((ch = getch()))
	{
		deal_with_this(ch);
		if (ch == '\n')
		{
			move_to(g_all.term.line_start + g_all.line_size);
			ft_printf("\n", g_all.line);
			dispatcher();
			ft_strdel(&g_all.line);
			start_line();
		}
	}
	return 0;
}
