/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:58 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/08 13:37:59 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_unset(t_shell *ms, char **cmd, int i, int j)
{
	while (cmd[i] != NULL)
	{
		j = 0;
		while (cmd[i][j] != '=' && cmd[i][j] != '\0')
			j++;
		if (cmd[i][j] != '=' && name_exists(ms, cmd[i]) == 0)
			envp_remove(ms, cmd[i]);
		i++;
	}
}