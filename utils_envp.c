/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
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
	//ms->envp[i] = ft_strdup(content);
	safe_strdup(&ms->envp[i], content, ms);
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
	new_envp = safe_calloc((ms->envp_size + 1) * sizeof(char *), ms);
	while (i < ms->envp_size)
	{
		if (ft_strncmp(ms->envp[j], "_=", 2) == 0)
		{
			//new_envp[i] = ft_strdup(content);
			safe_strdup(&new_envp[i], content, ms);
			i++;
		}
		//new_envp[i] = ft_strdup(ms->envp[j]);
		safe_strdup(&new_envp[j], content, ms);
		i++;
		j++;
	}
	new_envp[i] = NULL;
	free_double(&ms->envp);
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
	new_envp = safe_calloc((ms->envp_size + 1) * sizeof(char *), ms);
	while (i < ms->envp_size)
	{
		if (ft_strncmp(ms->envp[j], content, ft_strlen(content)) == 0)
			j++;
		//new_envp[i] = ft_strdup(ms->envp[j]);
		safe_strdup(&new_envp[i], ms->envp[j], ms);
		i++;
		j++;
	}
	new_envp[i] = NULL;
	free_double(&ms->envp);
	ms->envp = new_envp;
}
