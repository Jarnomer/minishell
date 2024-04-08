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
	char	*path;
	char	buf[1000];

	path = NULL;
	if (chdir(cmd[1]) == 0)
	{
		safe_strjoin(&path, "PWD=", getcwd(buf, 1000), ms);
		builtin_export(ms, &path, 0, 0);
	}
}