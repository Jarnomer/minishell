/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:09 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/08 13:37:10 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_export(t_shell *ms, char **cmd, int i, int j)
{
	if (cmd[i] == NULL)
		envp_print(ms->envp, ms->envp_size, 0, 0);
	while (cmd[i] != NULL)
	{
		j = 0;
		while (cmd[i][j] != '=' && cmd[i][j] != '\0')
			j++;
		if (cmd[i][j] == '=' && name_exists(ms, cmd[i]) == 0)
		{
			//doesnt work
			envp_update(ms, cmd[i]);
		}
		else if (name_exists(ms, cmd[i]) == 1)
		{
			//doesnt work
			envp_add(ms, cmd[i]);
		}
		i++;
	}
}
