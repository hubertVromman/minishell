/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:28:23 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/31 15:28:28 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nb_args(void)
{
	int		i;
	int		nb_args;

	i = 0;
	nb_args = 0;
	while (g_all.command.arguments[i])
	{
		while (g_all.command.arguments[i] == ' ')
			i++;
		if (g_all.command.arguments[i])
			nb_args++;
		while (g_all.command.arguments[i] != ' '
			&& g_all.command.arguments[i] != 0)
			i++;
	}
	return (nb_args);
}

static int	get_arguments(void)
{
	int		i;
	int		arg_nb;
	int		arg_len;

	i = 0;
	arg_nb = 0;
	while (g_all.command.arguments[i])
	{
		arg_nb++;
		if (arg_nb == g_all.command.nb_args)
			break ;
		while (g_all.command.arguments[i] == ' ')
			i++;
		if ((arg_len = ft_indexof(g_all.command.arguments + i, ' ')) == -1)
			arg_len = ft_strlen(g_all.command.arguments) - i;
		if (!(g_all.command.structured_args[arg_nb] =
			ft_strsub(g_all.command.arguments, i, arg_len)))
			exit_func(MERROR);
		i += arg_len;
	}
	return (0);
}

int			parse_arguments(void)
{
	g_all.command.nb_args = get_nb_args() + 1;
	if (!(g_all.command.structured_args =
		malloc(sizeof(char*) * (g_all.command.nb_args + 1))))
		exit_func(MERROR);
	if (!(g_all.command.structured_args[0] = ft_strdup(g_all.command.command)))
		exit_func(MERROR);
	get_arguments();
	g_all.command.structured_args[g_all.command.nb_args] = NULL;
	return (0);
}
