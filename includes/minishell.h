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

typedef struct	s_term
{
	int		line_start;
	int		cursor_pos;
	int		term_width;
	int		term_height;
	int		new_term_width;
	int		new_term_height;
}				t_term;


typedef struct	s_a
{
	char	*line;
	int		line_size;
	char	*command[10];
	t_term	term;
}				t_a;

t_a				g_all;

#endif
