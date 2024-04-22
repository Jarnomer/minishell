/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:14:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/22 19:11:12 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_occured(char *exec, char ***arr, t_module *mod, t_shell *ms)
{
	if (*arr != NULL)
		free(*arr);
	if (!mod)
		error_fatal(ENOMEM, MSG_MEM, ms);
	if (!exec)
		error_exit(ERR_CMD, mod->command->content, MSG_CMD, ms);
	else if (opendir(exec) != NULL)
		error_exit(ERR_FLDR, exec, MSG_FLDR, ms);
	else if (access(exec, F_OK) == SUCCESS
		&& access(exec, X_OK) == FAILURE)
		error_exit(ERR_PERM, exec, MSG_PERM, ms);
	else if (ft_strchr(exec, '/'))
		error_exit(ERR_CMD, exec, MSG_FILE, ms);
	else
		error_exit(ERR_CMD, exec, MSG_CMD, ms);
}

static char	*find_executable(char *binary, char *env, t_shell *ms)
{
	char	**paths;
	char	*exec;
	int		i;

	paths = ft_split(env, ':');
	if (!paths)
		error_fatal(ENOMEM, MSG_MEM, ms);
	i = 0;
	while (paths[i])
	{
		exec = ft_strjoin(paths[i++], binary);
		if (!exec)
			error_occured(NULL, &paths, NULL, ms);
		if (access(exec, F_OK) == SUCCESS)
			return (exec);
		free(exec);
	}
	return (NULL);
}

static char	*build_executable(t_module *mod, t_shell *ms)
{
	char	*path;
	char	*binary;

	path = NULL;
	if (!mod->command->content)
		return (NULL);
	binary = mod->command->content;
	if (!ft_strchr(binary, '/'))
	{
		binary = safe_trash(ft_strjoin("/", binary), ALLOCATED, ms);
		path = envp_exists("PATH", ms);
		if (!path)
			return (NULL);
		else
			return (find_executable(binary, path, ms));
	}
	return (binary);
}

void	execute_command(t_module *mod, t_shell *ms)
{
	char	**cmd;
	char	*exec;

	exec = build_executable(mod, ms);
	cmd = safe_double(mod->command, ms);
	if (!exec || execve(exec, cmd, ms->envp) == FAILURE)
		error_occured(exec, &cmd, mod, ms);
}
