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

# define REALLOC_SIZE 10
# define PROMPT "$>"

typedef struct	s_a
{
	char	*line;
	int		line_size;
	int		line_start_y;
	int		line_start_x;
	int		term_width;
	int		term_height;
	char	*command[10];
}				t_a;

t_a				g_all;

#endif