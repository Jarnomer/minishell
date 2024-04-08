/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:12:13 by vkinaret          #+#    #+#             */
/*   Updated: 2024/03/30 12:12:16 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int name_exists(t_shell *ms, char *name)
{
	int i;
	int size;

	i = 0;
	size = 0;
	while (name[size] != '=' && name[size] != '\0')
		size++;
	while (i < ms->envp_size)
	{
		if (ft_strncmp(ms->envp[i], name, size) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	execute_builtin(t_shell *ms, char **cmd)
{
	if (ft_strncmp("echo", cmd[0], 5) == 0)
		builtin_echo(ms, cmd);
	else if (ft_strncmp("cd", cmd[0], 3) == 0)
		builtin_cd(ms, cmd);
	else if (ft_strncmp("env", cmd[0], 4) == 0)
		builtin_env(ms->envp, 0, 0);
	else if (ft_strncmp("export", cmd[0], 7) == 0)
		builtin_export(ms, cmd, 1, 0);
	else if (ft_strncmp("unset", cmd[0], 6) == 0)
		builtin_unset(ms, cmd, 1, 0);
	else if (ft_strncmp("pwd", cmd[0], 4) == 0)
		builtin_pwd(ms, ms->envp);
	else if (ft_strncmp("exit", cmd[0], 5) == 0)
		exit(1);
	return (true);
}

int	is_builtin(t_shell *ms, char **cmd)
{
	if ((ft_strncmp("echo", cmd[0], 5) == 0 && ft_strlen(cmd[0]) == 5)
		|| (ft_strncmp("cd", cmd[0], 3) == 0 && ft_strlen(cmd[0]) == 3)
		|| (ft_strncmp("env", cmd[0], 4) == 0 && ft_strlen(cmd[0]) == 4)
		|| (ft_strncmp("export", cmd[0], 7) == 0 && ft_strlen(cmd[0]) == 7)
		|| (ft_strncmp("unset", cmd[0], 6) == 0 && ft_strlen(cmd[0]) == 6)
		|| (ft_strncmp("pwd", cmd[0], 4) == 0 && ft_strlen(cmd[0]) == 6)
		|| (ft_strncmp("exit", cmd[0], 5) == 0 && ft_strlen(cmd[0]) == 5))
		return (execute_builtin(ms, cmd));
	return (false);
}
