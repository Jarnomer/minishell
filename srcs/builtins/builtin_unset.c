/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:58 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/16 18:09:05 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	error_check(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]) || str[i] == '=')
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
			printf("str i: %s\n", cmd[i]);
			printf("char j = %c\n", cmd[i][j]);
			printf("envp_exists returned: %s\n", envp_exists(cmd[i], ms));
			if (cmd[i][j] != '=' && envp_exists(cmd[i], ms) != NULL)
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
