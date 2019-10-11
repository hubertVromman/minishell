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

#include <termios.h>
#include <errno.h>
#include <fcntl.h>


int get_pos(int *y, int *x) {

 char buf[30]={0};
 int ret, i, pow;
 char ch;

*y = 0; *x = 0;

 write(1, "\033[6n", 4);

 for( i = 0, ch = 0; ch != 'R'; i++ )
 {
    ret = read(0, &ch, 1);
    if ( !ret ) {
       // fprintf(stderr, "getpos: error reading response!\n");
       return 1;
    }
    buf[i] = ch;
    // ft_printf("buf[%d]: \t%c \t%d\n", i, ch, ch);
 }

 if (i < 2) {
    ft_printf("i < 2\n");
    return(1);
    }

    for( i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
       *x = *x + ( buf[i] - '0' ) * pow;

    for( i-- , pow = 1; buf[i] != '['; i--, pow *= 10)
       *y = *y + ( buf[i] - '0' ) * pow;
 return 0;
}

int getch(void) {
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

int		append_to_line(char ch)
{
	if (g_all.line_size == 0)
		if (!(g_all.line = malloc(REALLOC_SIZE + 1)))
			exit(0);
	++g_all.line_size;
	if ((g_all.line_size) % REALLOC_SIZE == 0)
		realloc_line();
	g_all.line[g_all.line_size - 1] = ch;
	g_all.line[g_all.line_size] = 0;
	return (0);
}

int		start_line()
{
	int		x;
	int		y;

	get_pos(&x, &y);
	g_all.line_start_y = y;
	g_all.line_start_x = x;

		ft_printf("%d %d", x, y);
	for (size_t i = 0; i < ft_strlen(PROMPT); ++i)
	{
		ft_printf("%c", PROMPT[i]);
	}
	return (0);
}

int		init()
{
	struct termios	org_opts;
	struct ttysize	ts;
	int				res;

	ft_bzero(&g_all, sizeof(g_all));
	ioctl(0, TIOCGSIZE, &ts);
	g_all.term_width = ts.ts_cols;
	g_all.term_height = ts.ts_lines;
	res = tcgetattr(0, &org_opts);
	ft_printf("%d width %d height %d\n", res, g_all.term_width, g_all.term_height);

	org_opts.c_lflag = ISIG & ~(ICANON);
	tcsetattr(0, TCSANOW, &org_opts);
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
			exit(0);
		}
		if (ch == 127)
		{
		// ft_printf("%d %d", x, y);
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
			/* Si pid == 0, alors on est dans le process fils. */
			else if (pid == 0)
			{
			// char **z=malloc(sizeof(char *) * 10);
			g_all.command[0] = "tput";
			g_all.command[1] = "cub";
			g_all.command[2] = "1";
			g_all.command[3] = NULL;
				if (execve("/usr/bin/tput", g_all.command, env) == -1)
					ft_printf("execve");
				return 1; /* On termine le fils même si execve fail parce qu'on veut voir que le pid du pere*/
			}
			/* Sinon, dans le pere. */
			else
				wait(&status); /* Oui, il faudrait vérifier la valeur de retour... */
			
			if ((pid = fork()) == -1)
			{
				ft_printf("%s\n", "fork");
				return 1;
			}
			/* Si pid == 0, alors on est dans le process fils. */
			else if (pid == 0)
			{
			// char **z=malloc(sizeof(char *) * 10);
			g_all.command[0] = "tput";
			g_all.command[1] = "clear";
			g_all.command[2] = NULL;
				if (execve("/usr/bin/tput", g_all.command, env) == -1)
					ft_printf("execve");
				return 1; /* On termine le fils même si execve fail parce qu'on veut voir que le pid du pere*/
			}
			/* Sinon, dans le pere. */
			else
				wait(&status); /* Oui, il faudrait vérifier la valeur de retour... */
			}
		}
		else
		{
			ft_printf("%c", ch);
			append_to_line(ch);
		}
		if (ch == '\n')
		{
			ft_printf("%s", g_all.line);
			g_all.line_size = 0;
			free(g_all.line);
			g_all.line = NULL;
			start_line();
		}
	}
	return 0;
}