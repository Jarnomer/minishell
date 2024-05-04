/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:17 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/24 16:14:19 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	symbol_check(char *str, int i)
{
	if ((str[0] == '-' || str[0] == '+') && ft_isdigit(str[1]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	if (str[0] != '+' && ft_strncmp(str, "9223372036854775807", 20) > 0)
		return (1);
	if (str[0] == '+' && ft_strncmp(str, "+9223372036854775807", 21) > 0)
		return (1);
	if (str[0] == '-' && ft_strncmp(str, "-9223372036854775808", 21) > 0)
		return (1);
	return (0);
}

void	builtin_exit(t_shell *ms, char **cmd)
{
	int	exit_code;

	exit_code = 0;
	if (cmd[1] && symbol_check(cmd[1], 0) == 1)
		error_exit(255, cmd[0], "numeric argument required", ms);
	if (cmd[2])
	{
		ft_putstr_fd("exit\n", 1);
		error_logger("exit: ", NULL, "too many arguments", ms);
		ms->excode = 1;
		return ;
	}
	if (cmd[1] && ft_atoi(cmd[1]) > -1)
		exit_code = (ft_atoi(cmd[1]) % 256);
	else if (cmd[1] && ft_atoi(cmd[1]) < 0)
		exit_code = (256 - ((ft_atoi(cmd[1]) * -1) % 256));
	if (ms->forks == 1)
		ft_putstr_fd("exit\n", 1);
	exit(exit_code);
}
