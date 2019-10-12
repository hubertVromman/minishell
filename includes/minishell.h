/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:33:18 by hvromman          #+#    #+#             */
/*   Updated: 2019/06/20 15:33:20 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <fcntl.h>
# include <limits.h>

# define RESET_COLOR "\e[0m"
# define HIDE_CURSOR "\e[?25l"
# define UNHIDE_CURSOR "\e[?25h"
# define CLEAR_SCREEN "\e[H\e[2J"
# define COLOR_PRINT "\e[%dm"
# define CHAR_HEX_PRINT "%.2hhx"
# define RGB_PRINT "\e[38;2;%.3d;%.3d;%.3dm"
# define RGB_PRINT_BG "\e[48;2;%.3d;%.3d;%.3dm"
# define SAVE_SCREEN "\e[?1049h"
# define RESTORE_SCREEN "\e[?1049l"
# define HOME_CURSOR "\e[H"

# define REALLOC_SIZE 10
# define PROMPT "$>"

# define SHELL_NAME "minishell"

typedef struct	s_term
{
	int		line_start;
	int		cursor_pos;
	int		term_width;
	int		term_height;
	int		new_term_width;
	int		new_term_height;
}				t_term;

typedef struct	s_command
{
	pid_t	child_pid;
	char	*command;
	char	*arguments;
	int		nb_args;
	char	**structured_args;
}				t_command;

typedef struct	s_a
{
	char		**env;
	char		*line;
	int			line_size;
	int			cursor_pos_in_line;
	t_command	command;
	t_term		term;
}				t_a;

t_a				g_all;

#endif

/*
** command_handler.c
*/
int				dispatcher();

/*
** error.c
*/
int				error(char *error_msg, char *details);

/*
** reader.c
*/
int				getch(void);
int				realloc_line();
int				append_to_line(char ch, int pos);
int				deal_with_this(char ch);

/*
** signal.c
*/
void			sig_winch(int c);

/*
** term_util.c
*/
int				get_pos(int *y, int *x);
int				move_to(int new_pos);
int				start_line();
