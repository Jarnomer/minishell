/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:10:57 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/07 19:03:54 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_executable(char **paths, char *temp)
{
	char	*exec;
	int		i;

	i = 0;
	while (paths[i])
	{
		exec = ft_strjoin(paths[i++], temp);
		if (access(exec, F_OK) == 0)
			return (exec);
		free(exec);
	}
	return (NULL);
}

static char	**path_envp_found(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (envp[i] != NULL)
		return (ft_split(envp[i] + 5, ':'));
	return (NULL);
}

char	*executable_path(char *exec, t_shell *ms)
{
	char	**paths;
	char	*temp;

	if (!exec || !*exec)
		return (NULL);
	else if (ft_strchr(exec, '/'))
		return (exec);
	paths = path_envp_found(ms->envp);
	temp = ft_strjoin("/", exec);
	if (!paths || !temp)
		return (NULL);
	return (find_executable(paths, temp));
}
