/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:14:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/17 20:24:51 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_occured(int errcode, char ***arr, t_module *mod, t_shell *ms)
{
	char	*exec;

	if (*arr != NULL)
		free(*arr);
	exec = mod->command->content;
	if (errcode == ENOMEM)
		error_fatal(ENOMEM, MSG_MEM, ms);
	else if (errcode == ERR_CMD)
		error_exit(ERR_CMD, exec, MSG_CMD, ms);
}

// static char	*check_command_errors(char *exec, t_module *mod, t_shell *ms)
// {

// }

static char	*find_executable(char *temp, char *path_envp, t_module *mod, t_shell *ms)
{
	char	**paths;
	char	*exec;
	int		i;

	paths = ft_split(path_envp, ':');
	if (!paths)
		error_fatal(ENOMEM, MSG_MEM, ms);
	i = 0;
	while (paths[i])
	{
		exec = ft_strjoin(paths[i++], temp);
		if (!exec)
			error_occured(ENOMEM, &paths, mod, ms);
		if (access(exec, F_OK) == SUCCESS)
			return (exec);
		free(exec);
	}
	return (NULL);
}

static char	*build_executable(t_module *mod, t_shell *ms)
{
	char	*path;
	char	*exec;

	path = NULL;
	exec = safe_trash(mod->command->content, ALLOCATE, ms);
	if (!ft_strchr(exec, '/'))
	{
		safe_strjoin(&exec, "/", exec, ms);
		path = envp_exists("PATH", ms);
		if (!path)
			return (NULL);
		else
			return (find_executable(exec, path, mod, ms));
	}
	return (exec);
}

void	execute_command(t_module *mod, t_shell *ms)
{
	char	**cmd;
	char	*exec;

	exec = build_executable(mod, ms);
	cmd = safe_double(mod->command, ms);
	// check_command_errors(exec, mod, ms);
	if (execve(exec, cmd, ms->envp) == FAILURE)
		error_occured(ERR_CMD, &cmd, mod, ms);
}
