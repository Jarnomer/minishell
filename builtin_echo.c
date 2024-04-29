/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:18 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/19 18:19:20 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flags(char *str)
{
	int i;

	i = 0;
	if (str[i] != '-')
		return (1);
	else
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	builtin_echo(char **cmd)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	while (cmd[i] && check_flags(cmd[i]) == 0)
	{
		n_flag = true;
		i++;
	}
	if (!cmd[i])
		ft_putchar_fd('\n', 1);
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1] == NULL && n_flag == false)
			ft_putchar_fd('\n', 1);
		else if (cmd[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
}
