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

static char	*name_exists(char *arg, t_shell *ms)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
		i++;
	name = safe_trash(ft_substr(arg, 0, i), ALLOCATED, ms);
	i = 0;
	len = ft_strlen(name);
	while (ms->envp[i])
	{
		if (ft_strncmp(ms->envp[i], name, len) == 0
			&& (ms->envp[i][len] == '\0' || ms->envp[i][len] == '='))
			return (ms->envp[i] + len);
		i++;
	}
	return (NULL);
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
	if (str[i] != '\0')
		return (1);
	return (0);
}

void	builtin_unset(t_shell *ms, char **cmd, int i, int j)
{
	while (cmd[i] != NULL)
	{
		j = 0;
		if (!error_check(cmd[i]))
		{
			if (name_exists(cmd[i], ms) != NULL)
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
