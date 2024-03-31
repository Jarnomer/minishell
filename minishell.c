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

//add a working history

int	main(void)
{
	t_shell	ms;

	ft_bzero(&ms, sizeof(t_shell));
	ms.prompt = ft_strdup("[ minishell ]$ ");
	ms.envp = init_envp(0, 0, &ms);
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
		ms.output = parse_input(&ms);
		//check if input is 'history' (display history list except for the current line)
		//add history after checking history
		if (check_if_builtin(&ms, ms.output) == 1)
			break ;
		else if (ms.output)
			printf("command line: %s\n", ms.output);
		//free input & free parse structs
		free(ms.input);
	}
	return (0);
}
