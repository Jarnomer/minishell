/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:58 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/05 15:52:58 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	char	*envp;

	while (cmd[i] != NULL)
	{
		j = 0;
		if (!error_check(cmd[i]))
		{
			while (cmd[i][j] != '=' && cmd[i][j] != '\0')
				j++;
			envp = safe_trash(ft_substr(cmd[i], 0, j), ALLOCATED, ms);
			if (cmd[i][j] != '=' && envp_exists(envp, ms) != NULL)
				envp_remove(ms, cmd[i]);
		}
		else
		{
			error_logger("unset: ", cmd[i], ": not a valid identifier", ms);
			ms->excode = 1;
		}
		i++;
	}
}