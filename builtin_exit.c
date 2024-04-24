/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:17 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/24 16:14:19 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void is_sign(char c)
{
	//check if char is a sign and that there is no more signs and that they're at the start
}*/

void	builtin_exit(t_shell *ms, char **cmd)
{
	int exit_code;

	exit_code = 0;
	if (ms->forks == 1)
		ft_putstr_fd("exit\n", 1);
	/*if (cmd[i])
	{
		if (i >= 2)
			//return error: too many arguments
		while (cmd[i][j])
		{
			if (ft_isdigit(cmd[i][j]) != 0 
				&& cmd[i][j] != '+' && cmd[i][j] != '-')
				//return error: is not a digit or sign
			j++;
		}
		//check if arguments only contain digits and signs
		//check if there is only one sign and it is at the start
		//check if number is greater than long_max
		//check if number is smaller than long_min
		i++;
	}*/
	if (cmd[1])
		exit_code = ft_atoi(cmd[1]);
	exit(exit_code);
}
