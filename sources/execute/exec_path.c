/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = safe_strjoin(dir, "/");
	full = safe_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

static char	*search_in_paths(char **paths, const char *cmd)
{
	char	*full_path;
	size_t	i;

	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_double((void ***)&paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_double((void ***)&paths);
	return (NULL);
}

bool	is_direct_path(const char *cmd)
{
	return (ft_strchr(cmd, '/') != NULL);
}

char	*resolve_path(const char *cmd, t_vec *env)
{
	char	*path_var;
	char	**paths;

	if (!cmd || !*cmd)
		return (NULL);
	if (is_direct_path(cmd))
	{
		if (access(cmd, X_OK) == 0)
			return (safe_strdup(cmd));
		return (NULL);
	}
	path_var = env_get(env, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	return (search_in_paths(paths, cmd));
}
