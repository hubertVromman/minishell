/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvromman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:05:11 by hvromman          #+#    #+#             */
/*   Updated: 2019/10/14 15:05:12 by hvromman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_atol_modified(char *str, long *nbr)
{
	int		i;
	int		sign;

	sign = 1;
	i = 0;
	if (str[i] == '-')
	{
		i++;
		sign = -1;
	}
	*nbr = 0;
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (*nbr > 922337203685477581 || (*nbr
	== 922337203685477580 && (str[i] - '0') > 6 + (sign < 0)))
			return (i);
		*nbr = *nbr * 10 + str[i] - '0';
		i++;
	}
	return (i);
}

int		exit_builtin()
{
	long	exit_status;
	int		pos;
	int		nb_digits;
	char	*str;
	int		len_error;

	if (g_all.command.nb_args > 2)
		error("exit:", " too many arguments");
	else if (g_all.command.nb_args == 2)
	{
		str = g_all.command.structured_args[1];
		nb_digits = ft_atol_modified(str, &exit_status);
		pos = nb_digits;
		while (ft_isdigit(str[pos++]))
			len_error = 1;
		pos--;
		if (len_error)
			ft_printf("minishell: number truncated after %d digits: %s\n%>",
				nb_digits, str, 2);
		if (str[pos])
		{
			ft_printf("minishell: bad math expression: `%s'\n%>", str + pos, 2);
			exit_status = 0;
		}
		exit_no_error(exit_status);
	}
	else
		exit_no_error(0);
	return (0);
}

