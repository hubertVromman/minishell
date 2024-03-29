/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 11:29:13 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/12 11:29:15 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_winch(int c)
{
	(void)c;
	ft_printf("windows resize\n");
}

void	sig_int(int c)
{
	(void)c;
	g_all.signal_sent = 1;
	g_all.command.exit_status = 1;
}
