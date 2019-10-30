/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:31:50 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/29 11:31:55 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		delete_var(int pos)
{
	free(g_all.var[pos]);
	ft_memcpy(g_all.var + pos, g_all.var + pos + 1, g_all.var_len - pos);
	g_all.var_len--;
	return (0);
}

int		modify_var(int pos, char *name, char *value)
{
	free(g_all.var[pos]);
	if (ft_printf("%s=%s%#>", name, value, &g_all.var[pos]) == -1)
		exit_func(MERROR);
	return (0);
}

int		add_var(char *name, char *value)
{
	char	**tmp;

	if (!(tmp = ft_memalloc(sizeof(*g_all.var) * (g_all.var_len + 2))))
		exit_func(MERROR);
	ft_memcpy(tmp, g_all.var, sizeof(*g_all.var) * g_all.var_len);
	free(g_all.var);
	g_all.var = tmp;
	if (ft_printf("%s=%s%#>", name, value, &g_all.var[g_all.var_len]) == -1)
		exit_func(MERROR);
	g_all.var_len++;
	g_all.var[g_all.var_len] = NULL;
	return (0);
}

int		change_or_add_var(char *name, char *value)
{
	int		pos;

	if ((pos = get_var_pos(name)) != -1)
	{
		modify_var(pos, name, value);
	}
	else
	{
		add_var(name, value);
	}
	return (0);
}

int		change_or_add_var_int(char *name, int value)
{
	int		pos;
	char	*tmp;

	if (!(tmp = ft_itoa(value)))
		exit_func(MERROR);
	if ((pos = get_var_pos(name)) != -1)
	{
		modify_var(pos, name, tmp);
	}
	else
	{
		add_var(name, tmp);
	}
	free(tmp);
	return (0);
}

int		init_var()
{
	g_all.var_len = 1 + 1;
	if (!(g_all.var = ft_memalloc(sizeof(*g_all.var) * (g_all.var_len))))
		exit_func(MERROR);
	if (!(g_all.var[0] = ft_strdup("?=0")))
		exit_func(MERROR);
	g_all.var[1] = NULL;
	return (0);
}
