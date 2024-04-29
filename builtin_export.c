/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:09 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/08 13:37:10 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_check(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	builtin_export(t_shell *ms, char **cmd, int i, int j)
{
	if (cmd[i] == NULL)
		envp_print(ms->envp, ms->envp_size, 0, 0);
	while (cmd[i] != NULL)
	{
		j = 0;
		if (!error_check(cmd[i]))
		{
			while (cmd[i][j] != '=' && cmd[i][j] != '\0')
				j++;
			if (cmd[i][j] == '=' && envp_exists(cmd[i], ms) != NULL)
				envp_update(ms, cmd[i]);
			else if (envp_exists(cmd[i], ms) == NULL)
				envp_add(ms, cmd[i]);
		}
		else
			error_logger("export: ", cmd[i], ": not a valid identifier", ms);
		i++;
	}
}
