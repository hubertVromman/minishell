/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 22:51:29 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/18 22:51:31 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		delete_env_var(int pos)
{
	free(g_all.env[pos]);
	ft_memcpy(g_all.env + pos, g_all.env + pos + 1, g_all.env_len - pos);
	g_all.env_len--;
	return (0);
}

int		modify_env_var(int pos, char *name, char *value)
{
	free(g_all.env[pos]);
	if (ft_printf("%s=%s%#>", name, value, &g_all.env[pos]) == -1)
		exit_func(MERROR);
	return (0);
}

int		add_env_var(char *name, char *value)
{
	char	**tmp;

	if (!(tmp = ft_memalloc(sizeof(*g_all.env) * (g_all.env_len + 2))))
		exit_func(MERROR);
	ft_memcpy(tmp, g_all.env, sizeof(*g_all.env) * g_all.env_len);
	free(g_all.env);
	g_all.env = tmp;
	if (ft_printf("%s=%s%#>", name, value, &g_all.env[g_all.env_len]) == -1)
		exit_func(MERROR);
	g_all.env_len++;
	g_all.env[g_all.env_len] = NULL;
	return (0);
}

int		init_env(char **env)
{
	int		i;

	if (env == NULL)
	{
		return (0);
	}
	g_all.env_len = ft_tablen((void**)env);
	if (!(g_all.env = ft_memalloc(sizeof(*g_all.env) * (g_all.env_len + 1))))
		exit_func(MERROR);
	i = -1;
	while (++i < g_all.env_len)
	{
		if (!(g_all.env[i] = ft_strdup(env[i])))
			exit_func(MERROR);
	}
	return (0);
}
