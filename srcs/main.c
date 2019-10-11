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


int get_pos(int *y, int *x) {

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

int		start_line()
{
	int		x;
	int		y;

	get_pos(&x, &y);
	g_all.term.line_start = y * g_all.term.term_width + x;
	g_all.term.cursor_pos = g_all.term.line_start;
	ft_printf("%s", PROMPT);
	return (0);
}

void	sig_winch(int c)
{
	(void)c;
	ft_printf("windows resize\n");
}

int		init()
{
	struct termios	org_opts;
	struct ttysize	ts;
	int				res;

	ft_bzero(&g_all, sizeof(g_all));
	ioctl(0, TIOCGSIZE, &ts);
	g_all.term.term_width = ts.ts_cols;
	g_all.term.term_height = ts.ts_lines;
	res = tcgetattr(0, &org_opts);
	ft_printf("res %d width %d height %d\n", res, g_all.term.term_width, g_all.term.term_height);

	org_opts.c_lflag = ISIG & ~(ICANON);
	tcsetattr(0, TCSANOW, &org_opts);
	signal(SIGWINCH, &sig_winch);
	start_line();
	return (0);
}

int		main(int ac, char **av, char **env)
{
	init();
	(void)ac;
	(void)av;
	char	ch;

	while ((ch = getch()))
	{
		if (ch == 4)
		{
			if (!g_all.line_size)
				exit(0);
		}
		else if (ch == 127)
		{
			if (g_all.line_size)
			{
				g_all.line_size--;
				g_all.line[g_all.line_size] = 0;


				int pid;
				int status;

				if ((pid = fork()) == -1)
				{
					ft_printf("%s\n", "fork");
					return 1;
				}
				else if (pid == 0)
				{
					g_all.command[0] = "tput";
					g_all.command[1] = "cub";
					g_all.command[2] = "1";
					g_all.command[3] = NULL;
					if (execve("/usr/bin/tput", g_all.command, env) == -1)
						ft_printf("execve");
					return 1; /* On termine le fils même si execve fail parce qu'on veut voir que le pid du pere*/
				}
				else
					wait(&status); /* Oui, il faudrait vérifier la valeur de retour... */

				// if ((pid = fork()) == -1)
				// {
				// 	ft_printf("%s\n", "fork");
				// 	return 1;
				// }
				// /* Si pid == 0, alors on est dans le process fils. */
				// else if (pid == 0)
				// {
				// // char **z=malloc(sizeof(char *) * 10);
				// 	g_all.command[0] = "tput";
				// 	g_all.command[1] = "clear";
				// 	g_all.command[2] = NULL;
				// 	if (execve("/usr/bin/tput", g_all.command, env) == -1)
				// 		ft_printf("execve");
				// 	return 1; /* On termine le fils même si execve fail parce qu'on veut voir que le pid du pere*/
				// }
				// else
				// 	wait(&status); /* Oui, il faudrait vérifier la valeur de retour... */
			}
		}
		else
		{
			append_to_line(ch, g_all.line_size);
			ft_printf("%s", g_all.line + g_all.line_size - 1);
		}
		if (ch == '\n')
		{
			ft_printf("%s", g_all.line);
			g_all.line_size = 0;
			ft_strdel(&g_all.line);
			start_line();
		}
	}
	return 0;
}
