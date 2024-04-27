/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:36:26 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/27 13:36:28 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_print(char **envp, int envp_size, int i, int j)
{
	int flag;

	while (i < envp_size)
	{
		j = 0;
		flag = 0;
		if (envp[i][0] == '_' && envp[i][1] == '=')
			break ;
		ft_putstr_fd("declare -x ", 1);
		while (envp[i][j] != '\0')
		{
			if (envp[i][j] == '=' && flag == 0)
			{
				ft_putchar_fd(envp[i][j], 1);
				ft_putchar_fd('\"', 1);
				flag = 1;
				j++;
			}
			ft_putchar_fd(envp[i][j], 1);
			j++;
		}
		if (flag == 1)
			ft_putchar_fd('\"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
