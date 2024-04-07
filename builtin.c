/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:12:13 by vkinaret          #+#    #+#             */
/*   Updated: 2024/03/30 12:12:16 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int name_exists(t_shell *ms, char *name)
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

static void builtin_unset(t_shell *ms, char *input, int i, int j)
{
	char **cmds;
	
	cmds = ft_split(input, ' ');
	while (cmds[i] != NULL)
	{
		j = 0;
		while (cmds[i][j] != '=' && cmds[i][j] != '\0')
			j++;
		if (cmds[i][j] != '=' && name_exists(ms, cmds[i]) == 0)
			envp_remove(ms, cmds[i]);
		free(cmds[i]);
		i++;
	}
	free(cmds[0]);
	free(cmds);
}

static void builtin_export(t_shell *ms, char *input, int i, int j)
{
	char **cmds;
	
	cmds = ft_split(input, ' ');
	if (cmds[i] == NULL)
		envp_print(ms->envp, ms->envp_size, 0, 0);
	while (cmds[i] != NULL)
	{
		j = 0;
		while (cmds[i][j] != '=' && cmds[i][j] != '\0')
			j++;
		if (cmds[i][j] == '=' && name_exists(ms, cmds[i]) == 0) 
			envp_update(ms, cmds[i]);
		else if (name_exists(ms, cmds[i]) == 1)
			envp_add(ms, cmds[i]);
		free(cmds[i]);
		i++;
	}
	free(cmds[0]);
	free(cmds);
}

static void builtin_env(char **envp, int i, int j)
{
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] != '=' && envp[i][j] != '\0')
			j++;
		if (envp[i][j] == '=')
			ft_putendl_fd(envp[i], 1);
		i++;
	}
}

int	check_if_builtin(t_shell *ms, char *cmd)
{
	char buf[1000];

	if (ft_strncmp("echo", cmd, 4) == 0)
	{
		if (ft_strncmp("echo -n", cmd, 7) == 0)
			ft_putstr_fd(cmd + 8, 1);
		else
			ft_putendl_fd(cmd + 5, 1);
	}
	else if (ft_strncmp("cd", cmd, 2) == 0)
	{
		if (chdir(cmd + 3) == 0)
			envp_update(ms, ft_strjoin("PWD=", getcwd(buf, 1000)));
	}
	else if (ft_strncmp("cwd", cmd, 4) == 0)
		printf("cwd: %s\n", getcwd(buf, 1000));
	else if (ft_strncmp("env", cmd, 4) == 0)
		builtin_env(ms->envp, 0, 0);
	else if (ft_strncmp("export", cmd, 6) == 0)
		builtin_export(ms, cmd, 1, 0);
	else if (ft_strncmp("unset", cmd, 5) == 0)
		builtin_unset(ms, cmd, 1, 0);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		ft_putendl_fd(getcwd(buf, 1000), 1);
	else if (ft_strncmp("exit", cmd, 5) == 0)
		return (1);
	return (0);
}
