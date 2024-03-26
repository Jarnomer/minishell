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

	ft_bzero(&ms, sizeof(t_shell));
	ms.prompt = ft_strdup("[ minishell ] ");
	while (true)
	{
		ms.input = readline(ms.prompt);
		if (!ms.input)
		{
			free_struct(&ms);
			printf("\nReceived EOF!\n");
			break ;
		}
		if (ft_strncmp("kill", ms.input, 5) == 0)
		{
			free_struct(&ms);
			printf("\nProgram ended successfully!\n");
			break ;
		}
		//parse the input, use 'output' in struct to set the correct message (compare to bash)
		ms.output = ms.input;
		printf("output: %s\n", ms.output);
		free(ms.input);
	}
	return (0);
}
