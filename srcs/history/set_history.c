/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_history.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 11:38:58 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/21 11:39:00 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		read_all_history_file()
{
	char	*file_content;

	file_content = read_full_file(g_all.history.read_fd);
	// ft_printf("%s\n", file_content);
	if (!(g_all.history.data = ft_strsplit(file_content, '\n')))
		exit_func(MERROR);
	g_all.history.size = ft_tablen((void**)g_all.history.data);
	g_all.history.malloc_size = g_all.history.size;
	free(file_content);
	return (0);
}

int		init_history()
{
	g_all.history.file_name = HISTORY_FILE;
	g_all.history.write_fd = open(g_all.history.file_name, O_CREAT | O_APPEND | O_WRONLY, 0600);
	if ((g_all.history.read_fd = open(g_all.history.file_name, O_RDONLY)) != -1)
		read_all_history_file();
	return (0);
}

int		add_to_history(char *data)
{
	//search for update (other other shells that write history file)
	if (g_all.history.size == g_all.history.malloc_size)
	{
		g_all.history.malloc_size += HISTORY_REALLOC_SIZE;
		g_all.history.data = realloc_buffer(g_all.history.data, g_all.history.size * sizeof(char*), g_all.history.malloc_size * sizeof(char*));
	}
	if (!(g_all.history.data[g_all.history.size] = ft_strdup(data)))
		exit_func(MERROR);
	g_all.history.size++;
	ft_printf("%d %s\n%>", g_all.history.size, data, g_all.history.write_fd);
	return (0);
}
