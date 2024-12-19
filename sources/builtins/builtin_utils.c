/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 12:12:13 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/06 17:57:23 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	exit_buildin(t_module *mod, t_shell *ms)
{
	if (ms->forks == 1 && is_builtin2(mod))
		return ;
	free_exit(ms);
	exit(ms->exitcode);
}

static int	handle_redirect(t_shell *ms, t_module *mod)
{
	if ((mod->infiles || mod->outfiles)
		&& parse_files(mod, ms) == -1)
		return (-1);
	return (0);
}

void	execute_builtin(t_shell *ms, t_module *mod)
{
	mod->cmd = safe_double(mod->command, ms);
	if (ms->forks == 1 && is_builtin2(mod) && handle_redirect(ms, mod))
		ms->exitcode = 1;
	else if (!ft_strncmp("echo", mod->cmd[0], 5))
		builtin_echo(ms, mod->cmd);
	else if (!ft_strncmp("cd", mod->cmd[0], 3))
		builtin_cd(ms, mod->cmd, NULL, NULL);
	else if (!ft_strncmp("env", mod->cmd[0], 4))
		builtin_env(ms, 0, 0);
	else if (!ft_strncmp("export", mod->cmd[0], 7))
		builtin_export(ms, mod->cmd, 1);
	else if (!ft_strncmp("unset", mod->cmd[0], 6))
		builtin_unset(ms, mod->cmd, 1);
	else if (!ft_strncmp("pwd", mod->cmd[0], 4))
		builtin_pwd(ms);
	else if (!ft_strncmp("exit", mod->cmd[0], 5))
		builtin_exit(ms, mod->cmd);
	exit_buildin(mod, ms);
}

bool	is_builtin2(t_module *mod)
{
	char	*cmd;
	int		len;
	int		args;

	if (!mod || !mod->command || !mod->command->content)
		return (false);
	args = parser_length(mod->command);
	cmd = mod->command->content;
	len = ft_strlen(cmd);
	if ((len == 6 && !ft_strncmp("export", cmd, len + 1) && args != 1)
		|| (len == 5 && !ft_strncmp("unset", cmd, len + 1))
		|| (len == 2 && !ft_strncmp("cd", cmd, len + 1))
		|| (len == 4 && !ft_strncmp("exit", cmd, len + 1)))
		return (true);
	return (false);
}

bool	is_builtin(t_module *mod)
{
	char	*cmd;
	int		len;
	int		args;

	if (!mod || !mod->command || !mod->command->content)
		return (false);
	args = parser_length(mod->command);
	cmd = mod->command->content;
	len = ft_strlen(cmd);
	if ((len == 6 && !ft_strncmp("export", cmd, len + 1) && args == 1)
		|| (len == 4 && !ft_strncmp("echo", cmd, len + 1))
		|| (len == 3 && !ft_strncmp("env", cmd, len + 1))
		|| (len == 3 && !ft_strncmp("pwd", cmd, len + 1))
		|| is_builtin2(mod))
		return (true);
	return (false);
}
