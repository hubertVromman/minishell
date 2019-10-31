/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:13:16 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/11 11:13:17 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_all(void)
{
	ft_free_tab((void***)&g_all.env);
	ft_free_tab((void***)&g_all.var);
	ft_free_tab((void***)&g_all.history.data);
	free_lines();
	return (0);
}

int		exit_func(int exit_code)
{
	if (exit_code == MERROR)
		ft_printf("malloc error\n%>", 2);
	else if (exit_code == HISTORY_FORMAT_ERROR)
		ft_printf("history read error\n%>", 2);
	free_all();
	exit(exit_code);
}

int		exit_no_error(int exit_code)
{
	free_all();
	exit(exit_code);
}
