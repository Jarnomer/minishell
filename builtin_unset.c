/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:58 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/29 17:56:46 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_check(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	builtin_unset(t_shell *ms, char **cmd, int i, int j)
{
	while (cmd[i] != NULL)
	{
		j = 0;
		if (!error_check(cmd[i]))
		{
			while (cmd[i][j] != '=' && cmd[i][j] != '\0')
				j++;
			if (cmd[i][j] != '=' && name_exists(ms, cmd[i]) == 0)
				envp_remove(ms, cmd[i]);
		}
		else
			error_logger("unset: ", cmd[i], ": not a valid identifier", ms);
		i++;
	}
}
