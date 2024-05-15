/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:37:09 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/05 15:52:54 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	name_exists(t_shell *ms, char *name)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (name[size] != '=' && name[size] != '\0')
		size++;
	while (i < ms->envp_size)
	{
		if (ft_strncmp(ms->envp[i], name, size) == 0)
			return (0);
		i++;
	}
	return (1);
}

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

void	builtin_export(t_shell *ms, char **cmd, int i, int j)
{
	char	*envp;

	if (cmd[i] == NULL)
		envp_print(ms, 0, 0);
	while (cmd[i] != NULL)
	{
		j = 0;
		if (!error_check(cmd[i]))
		{
			while (cmd[i][j] != '=' && cmd[i][j] != '\0')
				j++;
			envp = safe_trash(ft_substr(cmd[i], 0, j), ALLOCATED, ms);
			if (cmd[i][j] == '=' && name_exists(ms, cmd[i]) == 0)
				envp_update(ms, cmd[i]);
			else if (name_exists(ms, cmd[i]) == 1)
				envp_add(ms, cmd[i]);
		}
		else
		{
			error_logger("export: ", cmd[i], ": not a valid identifier", ms);
			ms->excode = 1;
		}
		i++;
	}
}
