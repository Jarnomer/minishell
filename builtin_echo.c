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

void	builtin_echo(char **cmd)
{
	int i;

	i = 1;
	if (cmd[i] && ft_strncmp("-n", cmd[i], 3) == 0)
	{
		while (cmd[++i] != NULL)
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1] != NULL)
				ft_putchar_fd(' ', 1);
		}
	}
	else
	{
		while(cmd[i] != NULL)
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1] == NULL)
				ft_putchar_fd('\n', 1);
			else
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
}
