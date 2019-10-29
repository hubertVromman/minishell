/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:12:58 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/21 12:12:59 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*realloc_buffer(void *prev_buf, int prev_size, int new_size)
{
	void	*tmp;
	int		copy_size;

	if (!(tmp = malloc(new_size)))
		exit_func(MERROR);
	if (prev_buf)
	{
		copy_size = prev_size < new_size ? prev_size : new_size;
		ft_memcpy(tmp, prev_buf, copy_size);
		free(prev_buf);
	}
	return (tmp);
}

char	*read_full_file(int fd)
{
	char	*buf;
	int		modifier;
	int		ret;
	int		real_size;

	buf = NULL;
	modifier = 1;
	real_size = 0;
	while ((long)modifier * HISTORY_BUFF_SIZE < INT_MAX / 2)
	{
		buf = realloc_buffer(buf, g_all.history.malloc_size, g_all.history.malloc_size + modifier * HISTORY_BUFF_SIZE);
		ret = read(fd, buf + g_all.history.malloc_size, modifier * HISTORY_BUFF_SIZE);
		if (ret == -1)
		{
			free(buf);
			return (NULL);
		}
		else if (ret == 0)
			break;
		real_size += ret;
		g_all.history.malloc_size += modifier * HISTORY_BUFF_SIZE;
		modifier *= 2;
	}
	if (real_size == g_all.history.malloc_size)
		buf = realloc_buffer(buf, g_all.history.malloc_size, g_all.history.malloc_size + 1);
	buf[real_size] = 0;
	return (buf);
}

char	*get_dir(char *path)
{
	static char	dir_name[PATH_MAX];
	int			ret;

	dir_name[0] = 0;
	if (!path)
		return (dir_name);
	if ((ret = ft_last_indexof(path, '/')) != -1)
	{
		ft_memcpy(dir_name, path, ret);
		dir_name[ret] = 0;
	}
	return (dir_name);
}

int		free_lines()
{
	if (g_all.line == g_all.current_line)

		ft_strdel(&g_all.line);
	else
	{
		ft_strdel(&g_all.line);
		ft_strdel(&g_all.current_line);
	}
	ft_strdel(&g_all.history.base);
	return (0);
}
