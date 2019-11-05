/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:28:31 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/31 15:28:33 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_dollar(char *line, int dollar_pos, int end)
{
	char	*replacement;
	char	*to_replace;
	int		final_len;
	char	*final_line;
	int		replacement_len;

	if (!(to_replace = ft_strsub(line, dollar_pos, end - dollar_pos)))
		exit_func(MERROR);
	if (!(replacement = get_env_var(to_replace + 1)))
		replacement = "";
	free(to_replace);
	replacement_len = ft_strlen(replacement);
	final_len = dollar_pos + replacement_len + ft_strlen(line) - end + 1;
	if (!(final_line = malloc(final_len)))
		exit_func(MERROR);
	ft_memcpy(final_line, line, dollar_pos);
	ft_memcpy(final_line + dollar_pos, replacement, replacement_len);
	ft_memcpy(final_line + dollar_pos + replacement_len, line + end,
		ft_strlen(line) - end + 1);
	return (final_line);
}

char	*search_dollar(char *line)
{
	int		dollar_pos;
	char	*tmp;
	int		end;

	while ((dollar_pos = ft_indexof(line, '$')) != -1)
	{
		end = dollar_pos + 1;
		while (ft_isalnum(line[end]))
			end++;
		if (end != dollar_pos + 1)
		{
			tmp = replace_dollar(line, dollar_pos, end);
			end = dollar_pos + 1;
			free(line);
			line = tmp;
		}
	}
	g_all.line_size = ft_strlen(line);
	return (line);
}
