/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:48 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/29 17:57:04 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_envp_values(t_shell *ms, char *pwd, char *oldpwd)
{
	if (name_exists(ms, "PWD") == 0)
		envp_update(ms, pwd);
	if (name_exists(ms, "OLDPWD") == 0)
		envp_update(ms, oldpwd);
}

void	builtin_cd(t_shell *ms, char **cmd)
{
	char	*pwd;
	char	*oldpwd;
	char	*home;
	char	buf[1000];

	pwd = NULL;
	oldpwd = NULL;
	home = envp_exists("HOME", ms);
	safe_strjoin(&oldpwd, "OLDPWD=", envp_exists("PWD", ms), ms);
	if (!cmd[1] && chdir(home) == 0)
	{
		safe_strjoin(&pwd, "PWD=", getcwd(buf, 1000), ms);
		update_envp_values(ms, pwd, oldpwd);
	}
	else if (chdir(cmd[1]) == 0)
	{
		safe_strjoin(&pwd, "PWD=", getcwd(buf, 1000), ms);
		update_envp_values(ms, pwd, oldpwd);
	}
	else
		error_logger("cd: ", cmd[1], ": No such file or directory", ms);
}
