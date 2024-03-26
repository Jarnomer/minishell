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

static void	free_struct(t_shell *ms)
{
	if (ms->prompt)
		free(ms->prompt);
	if (ms->input)
		free(ms->input);
}

int	main(void)
{
	t_shell	ms;
	extern char **environ;

	ft_bzero(&ms, sizeof(t_shell));
	ms.prompt = ft_strdup("[ minishell ] ");
	//copy the environ to ms.envp
	ms.envp = environ;
	while (true)
	{
		ms.input = readline(ms.prompt);
		if (!ms.input)
		{
			free_struct(&ms);
			printf("\nReceived EOF!\n");
			break ;
		}
		//parse the input, use 'output' in struct to set the correct message (compare to bash)
		ms.output = ms.input;
		//check if input is 'exit'
		if (ft_strncmp("exit", ms.input, 5) == 0)
		{
			free_struct(&ms);
			printf("\nProgram ended successfully!\n");
			break ;
		}
		//check if input is 'env'
		else if (ft_strncmp("env", ms.input, 5) == 0)
		{
			int i = 0;
			while (ms.envp[i] != 0)
			{
				printf("%s\n", ms.envp[i]);
				i++;
			}
		}
		//check if input is 'pwd'
		else if (ft_strncmp("pwd", ms.input, 5) == 0)
			printf("%s\n", getenv("PWD"));
		else
			printf("output: %s\n", ms.output);
		free(ms.input);
	}
	return (0);
}
