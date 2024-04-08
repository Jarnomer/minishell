/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:18 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/08 13:37:19 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_shell *ms, char **cmd)
{
	int i;

	i = 1;
	if (ft_strncmp("-n", cmd[i], 3) == 0)
	{
		while (cmd[++i] != NULL)
			ft_putstr_fd(cmd[i], 1);
	}
	else
	{
		while(cmd[i] != NULL)
		{
			ft_putstr_fd(cmd[i], 1);
			i++;
		}
	}
}