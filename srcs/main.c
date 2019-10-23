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
	// g_all.env = env;
	init_env(env);
	init_history();
	ioctl(0, TIOCGSIZE, &ts);
	g_all.term.term_width = ts.ts_cols;
	g_all.term.term_height = ts.ts_lines;
	res = tcgetattr(0, &org_opts);
	// ft_printf("res %d width %d height %d\n", res, g_all.term.term_width, g_all.term.term_height);
	org_opts.c_lflag = (ISIG | OFDEL | IEXTEN) & ~(ICANON); // not sure for ofdel
	tcsetattr(0, TCSANOW, &org_opts);
	signal(SIGWINCH, &sig_winch);
	signal(SIGINT, &sig_int);
	return (0);
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	ch;

	init(env);
	for (int i = 0; i < 5; i++)
	{
		if (start_line() == -1)
			exit_func(-2);
		g_all.signal_sent = 0;
		while ((ch = getch_killable()) != '\n')
		{
			deal_with_this(ch);
		}
		move_to(g_all.term.line_start + g_all.line_size);
		ft_printf("\n");
		if (g_all.signal_sent)
		{
			free_lines();
			g_all.line_size = 0;
			continue;
		}
		dispatcher();
		free_lines();
		g_all.line_size = 0;
	}
	return 0;
}
