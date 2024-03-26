/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:02:18 by vkinaret          #+#    #+#             */
/*   Updated: 2024/03/26 17:02:19 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	int i = 0;
	char *command_line = 0;

	while (i != 1)
	{
		command_line = readline("[ minishell ] ");
		printf("output: %s\n", command_line); 
		if (ft_strncmp("kill", command_line, 5) == 0)
		{
			free(command_line);
			break ;
		}
		free(command_line);
	}
	printf("\nkill ended the program successfully!\n");
	return (0);
}
