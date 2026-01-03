/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

static void	exec_child(t_cmd *cmd, t_shell *shell, char *path)
{
	char	**argv;
	char	**envp;

	setup_signals_child();
	if (apply_redirs(&cmd->redirs) == -1)
		exit(EC_FAILURE);
	argv = vec_to_arr(&cmd->args);
	envp = vec_to_arr(&shell->env);
	if (!argv || !envp)
		exit(EC_FAILURE);
	execve(path, argv, envp);
	perror("minishell: execve");
	exit(EC_FAILURE);
}

static int	exec_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_fds[2];
	int	status;

	if (save_std_fds(saved_fds) == -1)
		return (EC_FAILURE);
	if (apply_redirs(&cmd->redirs) == -1)
	{
		restore_std_fds(saved_fds);
		return (EC_FAILURE);
	}
	status = run_builtin(cmd, shell);
	restore_std_fds(saved_fds);
	return (status);
}

static int	wait_and_get_status(pid_t pid)
{
	int	status;

	setup_signals_ignore();
	waitpid(pid, &status, 0);
	setup_signals_interactive();
	return (get_exit_status(status));
}

static int	exec_external(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*name;
	pid_t	pid;

	name = vec_get(&cmd->args, 0);
	path = resolve_path(name, &shell->env);
	if (!path)
		return (check_cmd_error(name));
	pid = try_fork(NULL, 0);
	if (pid == -1)
	{
		free(path);
		return (EC_FAILURE);
	}
	if (pid == 0)
		exec_child(cmd, shell, path);
	free(path);
	return (wait_and_get_status(pid));
}

int	exec_simple_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*name;
	int		saved_fds[2];

	if (!cmd || cmd->args.len == 0)
	{
		if (cmd && cmd->redirs.len > 0)
		{
			if (save_std_fds(saved_fds) == -1)
				return (EC_FAILURE);
			if (apply_redirs(&cmd->redirs) == -1)
			{
				restore_std_fds(saved_fds);
				return (EC_FAILURE);
			}
			restore_std_fds(saved_fds);
		}
		return (EC_SUCCESS);
	}
	name = vec_get(&cmd->args, 0);
	if (is_builtin(name))
		return (exec_builtin(cmd, shell));
	return (exec_external(cmd, shell));
}
