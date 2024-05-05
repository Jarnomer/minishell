/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:36:26 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/05 15:53:19 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_single_variable(char *var, int j)
{
	int	flag;

	flag = 0;
	while (var[j] != '\0')
	{
		if (var[j] == '=' && flag == 0)
		{
			ft_putchar_fd(var[j], 1);
			ft_putchar_fd('\"', 1);
			flag = 1;
			j++;
		}
		ft_putchar_fd(var[j], 1);
		j++;
	}
	if (flag == 1)
		ft_putchar_fd('\"', 1);
	ft_putchar_fd('\n', 1);
}

static int	is_not_on_the_list(char *var, char **list)
{
	int	i;

	i = 0;
	while (list[i] != NULL)
	{
		if (ft_strncmp(var, list[i], ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

static char	*find_top_item(char **envp, char **sorted_list)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (is_not_on_the_list(envp[i], sorted_list) == 0)
			break ;
		i++;
	}
	return (envp[i]);
}

static char	**sort_envp_list(char **envp, int envp_size, t_shell *ms)
{
	int		i;
	int		j;
	char	*top;
	char	**sorted_list;

	i = 0;
	sorted_list = safe_calloc((envp_size + 1) * sizeof(char *), ms);
	while (i < envp_size)
	{
		j = 1;
		top = envp[0];
		if (is_not_on_the_list(top, sorted_list) == 1)
			top = find_top_item(envp, sorted_list);
		while (j < envp_size)
		{
			if (ft_strncmp(top, envp[j], ft_strlen(top)) > 0
				&& is_not_on_the_list(envp[j], sorted_list) == 0)
				top = envp[j];
			j++;
		}
		sorted_list[i] = top;
		i++;
	}
	return (sorted_list);
}

void	envp_print(t_shell *ms, int i, int j)
{
	char	**sorted_list;

	sorted_list = sort_envp_list(ms->envp, ms->envp_size, ms);
	while (i < ms->envp_size)
	{
		if (sorted_list[i][j] == '_' && sorted_list[i][j + 1] == '=')
			i++;
		if (i < ms->envp_size)
		{
			ft_putstr_fd("declare -x ", 1);
			print_single_variable(sorted_list[i], j);
			i++;
		}
	}
	free(sorted_list);
}
