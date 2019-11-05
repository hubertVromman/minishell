/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:20:47 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/31 15:20:49 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_var(void)
{
	g_all.var_len = 1 + 1;
	if (!(g_all.var = ft_memalloc(sizeof(*g_all.var) * (g_all.var_len))))
		exit_func(MERROR);
	if (!(g_all.var[0] = ft_strdup("?=0")))
		exit_func(MERROR);
	g_all.var[1] = NULL;
	return (0);
}
