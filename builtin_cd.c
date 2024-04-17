/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:48 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/08 13:37:50 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(t_shell *ms, char **cmd)
{
	char	*pwd;
	char	*oldpwd;
	char	buf[1000];

	pwd = NULL;
	oldpwd = NULL;
	safe_strjoin(&oldpwd, "OLDPWD=", envp_exists(ms, "PWD"), ms);
	if (chdir(cmd[1]) == 0)
	{
		safe_strjoin(&pwd, "PWD=", getcwd(buf, 1000), ms);
		envp_update(ms, pwd);
		envp_update(ms, oldpwd);
	}
}