/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 13:09:20 by vkinaret          #+#    #+#             */
/*   Updated: 2024/03/30 13:09:22 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_print(char **envp, int envp_size, int i, int flag)
{
	int j;

	while (i < envp_size)
	{
		j = 0;
		if (envp[i][j] == '_' && envp[i][j + 1] == '=')
			break ;
		printf("declare -x ");
		while (envp[i][j] != '\0')
		{
			if (envp[i][j] == '=')
			{
				printf("%c", envp[i][j]);
				printf("\"");
				flag = 1;
				j++;
			}
			printf("%c", envp[i][j]);
			j++;
		}
		if (flag == 1)
			printf("\"");
		printf("\n");
		i++;
	}
}

void	envp_update(t_shell *ms, char *content)
{
	int		i;
	int		size;
	char	*temp;

	i = 0;
	size = 0;
	while (content[size] != '=')
		size++;
	while (i < ms->envp_size)
	{
		if (ft_strncmp(ms->envp[i], content, size) == 0)
			break ;
		i++;
	}
	temp = ms->envp[i];
	ms->envp[i] = ft_strdup(content);
	free(temp);
}

void	envp_add(t_shell *ms, char *content)
{
	int 	i;
	int 	j;
	char	**new_envp;

	i = 0;
	j = 0;
	ms->envp_size += 1;
	new_envp = ft_calloc(ms->envp_size + 1, sizeof(char *));
	while (i < ms->envp_size)
	{
		if (ft_strncmp(ms->envp[j], "_=", 2) == 0)
		{
			new_envp[i] = ft_strdup(content);
			i++;
		}
		new_envp[i] = ft_strdup(ms->envp[j]);
		i++;
		j++;
	}
	new_envp[i] = NULL;
	free_envp(ms);
	ms->envp = new_envp;
}

void	envp_remove(t_shell *ms, char *content)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	ms->envp_size -= 1;
	new_envp = ft_calloc(ms->envp_size + 1, sizeof(char *));
	while (i < ms->envp_size)
	{
		if (ft_strncmp(ms->envp[j], content, ft_strlen(content)) == 0)
			j++;
		new_envp[i] = ft_strdup(ms->envp[j]);
		i++;
		j++;
	}
	new_envp[i] = NULL;
	free_envp(ms);
	ms->envp = new_envp;
}

char	**init_envp(int i, int size, t_shell *ms)
{
	char		**envp;
	extern char	**environ;

	while (environ[size] != NULL)
		size++;
	ms->envp_size = size;
	envp = ft_calloc(size + 1, sizeof(char *));
	while (i < size)
	{
		envp[i] = ft_strdup(environ[i]);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
