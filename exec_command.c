/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:14:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/17 17:15:10 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_executable(char **paths, char *temp)
{
	char	*exec;
	int		i;

	i = 0;
	while (paths[i])
	{
		exec = ft_strjoin(paths[i++], temp);
		if (access(exec, F_OK) == 0)
			return (exec);
		free(exec);
	}
	return (NULL);
}

static char	**path_envp_found(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (envp[i] != NULL)
		return (ft_split(envp[i] + 5, ':'));
	return (NULL);
}

static char	*executable_path(char *exec, t_shell *ms)
{
	char	**paths;
	char	*temp;

	if (!exec || !*exec)
		return (NULL);
	else if (ft_strchr(exec, '/'))
		return (exec);
	paths = path_envp_found(ms->envp);
	temp = ft_strjoin("/", exec);
	if (!paths || !temp)
		return (NULL);
	return (find_executable(paths, temp));
}

static char	**build_command(t_parser *command, t_shell *ms)
{
	char	**cmd;
	int		len;
	int		i;

	len = parser_length(command) + 1;
	cmd = safe_calloc(len * sizeof(char *), ms);
	i = 0;
	while (command)
	{
		cmd[i] = command->content;
		command = command->next;
		i++;
	}
	return (cmd);
}

void	execute_command(t_module *mod, t_shell *ms)
{
	char	**cmd;
	char	*exec;

	exec = mod->command->content;
	exec = executable_path(exec, ms);
	// TODO add command error handling here
	cmd = build_command(mod->command, ms);
	execve(exec, cmd, ms->envp);
	free(cmd);
	error_exit(NOERROR, NULL, NULL, ms);
}
