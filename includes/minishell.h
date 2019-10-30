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

/*
** my includes
*/

# include "libft.h"
# include "prototypes.h"

/*
** libraries includes
*/

# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

/*
** defines
*/

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
# define MOVE_TO "\e[%d;%dH"

# define REALLOC_SIZE 10
# define PROMPT "$> "

# define SHELL_NAME "minishell"
# define COMMAND_MAX_LEN 1000
# define MERROR -2
# define HISTORY_FORMAT_ERROR -3

# define HISTORY_FILE "/Users/hvromman/.minishell_history"
# define HISTORY_BUFF_SIZE 1000
# define HISTORY_REALLOC_SIZE 30

/*
** structures
*/

typedef struct	s_history
{
	int		pos_in_history;
	int		cursor_pos_in_base;
	int		base_pos;
	char	*base;
	int		read_fd;
	int		write_fd;
	int		malloc_size;
	int		size;
	char	*file_name;
	char	**data;
}				t_history;

typedef struct	s_term
{
	int		line_start;
	int		cursor_pos;
	int		term_width;
	int		term_height;
	int		new_term_width;
	int		new_term_height;
	int		prompt_size;
}				t_term;

typedef struct	s_command
{
	pid_t			child_pid;
	char			*command;
	char			command_expanded[PATH_MAX];
	char			*arguments;
	int				nb_args;
	char			**structured_args;
	unsigned char	exit_status;
}				t_command;

typedef struct	s_a
{
	int			signal_sent;
	int			exit;
	int			env_len;
	char		**env;
	int			var_len;
	char		**var;
	char		*line;
	char		*current_line;
	int			pos_in_command;
	char		*current_command_line;
	int			line_malloc_size;
	int			line_size;
	int			cursor_pos_in_line;
	t_command	command;
	t_history	history;
	t_term		term;
}				t_a;

t_a				g_all;

#endif
