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
	init_var();
	init_env(env);
	init_history();
	ioctl(0, TIOCGSIZE, &ts);
	g_all.term.term_width = ts.ts_cols;
	g_all.term.term_height = ts.ts_lines;
	res = tcgetattr(0, &org_opts);
	org_opts.c_lflag = (ISIG | OFDEL | IEXTEN) & ~(ICANON);
	tcsetattr(0, TCSANOW, &org_opts);
	signal(SIGWINCH, &sig_winch);
	signal(SIGINT, &sig_int);
	return (0);
}

int		main(int ac, char **av, char **env)
{
	char	ch;

	(void)ac;
	(void)av;
	init(env);
	ft_printf("%s\n", NULL);
	while (1)
	{
		if (start_line() == -1)
			exit_func(-2);
		g_all.signal_sent = 0;
		while ((ch = getch_killable()) != '\n')
			deal_with_this(ch);
		move_to(g_all.term.line_start + g_all.line_size) || ft_printf("\n");
		if (!g_all.signal_sent)
		{
			append_to_line(0, g_all.line_size);
			if (!(g_all.current_command_line = ft_strdup(g_all.current_line)))
				exit_func(MERROR);
			g_all.pos_in_command = 0;
			parser();
		}
		g_all.line_size = 0 || free_lines();
		change_or_add_var_int("?", g_all.command.exit_status);
	}
	return (0);
}
