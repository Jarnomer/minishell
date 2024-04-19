/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:12:13 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/19 19:27:27 by jmertane         ###   ########.fr       */
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

void	execute_builtin(t_shell *ms, t_module *mod)
{
	char **cmd;

	cmd = safe_double(mod->command, ms);
	if (ft_strncmp("echo", cmd[0], 4) == 0)
		builtin_echo(cmd);
	else if (ft_strncmp("cd", cmd[0], 2) == 0)
		builtin_cd(ms, cmd);
	else if (ft_strncmp("env", cmd[0], 3) == 0)
		builtin_env(ms->envp, 0, 0);
	else if (ft_strncmp("export", cmd[0], 6) == 0)
		builtin_export(ms, cmd, 1, 0);
	else if (ft_strncmp("unset", cmd[0], 5) == 0)
		builtin_unset(ms, cmd, 1, 0);
	else if (ft_strncmp("pwd", cmd[0], 3) == 0)
		builtin_pwd(ms, ms->envp);
	else if (ft_strncmp("exit", cmd[0], 4) == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
}

bool	is_builtin2(t_module *mod)
{
	char	*cmd;

	if (!mod || !mod->command)
		return (false);
	cmd = mod->command->content;
	if (ft_strncmp("cd", cmd, 3) == SUCCESS
		|| ft_strncmp("export", cmd, 7) == SUCCESS
		|| ft_strncmp("unset", cmd, 6) == SUCCESS
		|| ft_strncmp("exit", cmd, 5) == SUCCESS)
		return (true);
	return (false);
}

bool	is_builtin(t_module *mod)
{
	char	*cmd;

	if (!mod || !mod->command)
		return (false);
	cmd = mod->command->content;
	if (ft_strncmp("echo", cmd, 5) == SUCCESS
		|| ft_strncmp("env", cmd, 4) == SUCCESS
		|| ft_strncmp("pwd", cmd, 4) == SUCCESS
		|| is_builtin2(mod))
		return (true);
	return (false);
}
