/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:13:35 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/31 15:13:37 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_line_size(char *file_content, int size)
{
	while (file_content[size] != '\n' && file_content[size])
		size++;
	if (size && file_content[size] == '\\')
		return (get_line_size(file_content + size + 1, size));
	return (size);
}

int		get_history_size(char *file_content)
{
	int		size;
	int		reader;
	int		ret;

	size = 0;
	reader = 0;
	while ((ret = get_line_size(file_content + reader, 0)))
	{
		reader += ret + 1;
		size++;
	}
	return (size);
}

char	*get_line(char *file_content, int *line_size)
{
	int		offset;

	*line_size = get_line_size(file_content, 0);
	offset = 0;
	while (file_content[offset] != ';' && file_content[offset])
		offset++;
	if (file_content[offset])
		offset++;
	if (file_content[offset] == ' ')
		offset++;
	if (!file_content[offset])
		return (NULL);
	return (ft_strsub(file_content, offset, *line_size - offset));
}

char	**parse_history_file(char *file_content)
{
	char	**data;
	int		history_size;
	int		line_count;
	int		line_size;
	int		reader;

	history_size = get_history_size(file_content);
	if (!(data = malloc((history_size + 1) * sizeof(char*))))
		return (NULL);
	line_count = -1;
	reader = 0;
	while (++line_count < history_size)
	{
		if (!(data[line_count] = get_line(file_content + reader, &line_size)))
		{
			ft_free_tab((void***)&data);
			return (NULL);
		}
		reader += line_size + 1;
	}
	data[line_count] = NULL;
	return (data);
}

int		read_all_history_file(void)
{
	char	*file_content;

	file_content = read_full_file(g_all.history.read_fd);
	if (!(g_all.history.data = parse_history_file(file_content)))
		exit_func(HISTORY_FORMAT_ERROR);
	g_all.history.size = ft_tablen((void**)g_all.history.data);
	g_all.history.malloc_size = g_all.history.size;
	free(file_content);
	return (0);
}
