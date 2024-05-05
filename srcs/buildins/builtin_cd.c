/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:48 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/05 15:52:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	update_envp_values(t_shell *ms, char *pwd, char *oldpwd, char *buf)
{
	safe_strjoin(&pwd, "PWD=", getcwd(buf, 1000), ms);
	if (envp_exists("PWD", ms) != NULL)
		envp_update(ms, pwd);
	if (envp_exists("OLDPWD", ms) != NULL)
		envp_update(ms, oldpwd);
	ms->excode = 0;
}

void	builtin_cd(t_shell *ms, char **cmd, char *pwd, char *oldpwd)
{
	char	*home;
	char	buf[1000];

	home = envp_exists("HOME", ms);
	if (home == NULL)
	{
		error_logger("cd: ", NULL, "HOME not set", ms);
		ms->excode = 1;
		return ;
	}
	oldpwd = safe_trash(ft_strjoin("OLDPWD=", envp_exists("PWD", ms)),
			ALLOCATED, ms);
	if (!cmd[1] && chdir(home) == 0)
		update_envp_values(ms, pwd, oldpwd, buf);
	else if (chdir(cmd[1]) == 0)
		update_envp_values(ms, pwd, oldpwd, buf);
	else
	{
		error_logger("cd: ", cmd[1], ": No such file or directory", ms);
		ms->excode = 1;
	}
}
