/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:48 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/09 16:46:43 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	error_occured(t_shell *ms, char **cmd)
{
	struct stat	info;
	int			sstat;

	sstat = stat(cmd[1], &info);
	if (ft_strlen(cmd[1]) > 255)
	{
		error_logger("cd: ", cmd[1], ": File name too long", ms);
		ms->excode = 1;
	}
	else if (!sstat && S_ISREG(info.st_mode))
	{
		error_logger("cd: ", cmd[1], ": Not a directory", ms);
		ms->excode = 1;
	}
	else if (!sstat && S_ISDIR(info.st_mode) && access(cmd[1], R_OK) == -1)
	{
		error_logger("cd: ", cmd[1], ": Permission denied", ms);
		ms->excode = 1;
	}
	else if (sstat == -1)
	{
		error_logger("cd: ", cmd[1], ": No such file or directory", ms);
		ms->excode = 1;
	}
	return (ms->excode);
}

static void	update_envp_values(t_shell *ms, char *pwd, char *oldpwd, char *buf)
{
	char	*temp;

	free_single(&ms->cwd);
	if (!pwd)
	{
		pwd = safe_trash(ft_strjoin("PWD=", getcwd(buf, 1000)), ALLOCATED, ms);
		safe_strdup(&ms->cwd, pwd + 4, ms);
	}
	else
	{
		temp = pwd;
		pwd = safe_trash(ft_strjoin("PWD=", temp), ALLOCATED, ms);
		free(temp);
		safe_strdup(&ms->cwd, pwd + 4, ms);
	}
	if (envp_exists("PWD", ms) != NULL)
		envp_update(ms, pwd);
	if (envp_exists("OLDPWD", ms) != NULL)
		envp_update(ms, oldpwd);
	ms->excode = 0;
}

static int	check_home(t_shell *ms, char **cmd, char *pwd, char *oldpwd)
{
	char	*home;
	char	buf[1000];

	home = envp_exists("HOME", ms);
	if (!home && (!cmd[1] || !*cmd[1]))
	{
		error_logger("cd: ", NULL, "HOME not set", ms);
		ms->excode = 1;
		return (1);
	}
	if (!cmd[1] && chdir(home) == 0)
	{
		update_envp_values(ms, pwd, oldpwd, buf);
		return (2);
	}
	if ((!cmd[1] || !*cmd[1]) && home && !*home)
		return (2);
	if (!cmd[1] && *home)
	{
		error_logger("cd: ", home, ": No such file or directory", ms);
		ms->excode = 1;
		return (1);
	}
	return (0);
}

static void	getcwd_is_null(t_shell *ms, char **cmd, char *pwd, char *oldpwd)
{
	char	*temp;
	char	buffer[1000];

	oldpwd = safe_trash(ft_strjoin("OLDPWD=", ms->cwd), ALLOCATED, ms);
	if (check_home(ms, cmd, pwd, oldpwd) > 0 || error_occured(ms, cmd) > 0)
		return ;
	if (cmd[1] && chdir(cmd[1]) == 0)
	{
		if (getcwd(buffer, 1000) == NULL)
		{
			error_logger("cd: error retrieving current directory: ",
				CWD_ERR, "No such file or directory", ms);
			temp = safe_trash(ft_strjoin(ms->cwd, "/"), ALLOCATED, ms);
			safe_strjoin(&pwd, temp, cmd[1], ms);
		}
		update_envp_values(ms, pwd, oldpwd, buffer);
	}
	else
	{
		error_logger("cd: ", cmd[1], ": No such file or directory", ms);
		ms->excode = 1;
	}
}

void	builtin_cd(t_shell *ms, char **cmd, char *pwd, char *oldpwd)
{
	char	buf[1000];

	if (getcwd(buf, 1000) == NULL)
	{
		getcwd_is_null(ms, cmd, pwd, oldpwd);
		return ;
	}
	oldpwd = safe_trash(ft_strjoin("OLDPWD=", getcwd(buf, 1000)),
			ALLOCATED, ms);
	if (check_home(ms, cmd, pwd, oldpwd) > 0 || error_occured(ms, cmd) > 0)
		return ;
	if (cmd[1] && chdir(cmd[1]) == 0)
		update_envp_values(ms, pwd, oldpwd, buf);
	else
	{
		error_logger("cd: ", cmd[1], ": No such file or directory", ms);
		ms->excode = 1;
	}
}
