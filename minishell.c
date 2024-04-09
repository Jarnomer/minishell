/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:23 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/09 13:15:27 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_shell	ms;

	init_shell(&ms);
	while (true)
	{
		ms.input = readline(ms.prompt);
		if (!ms.input || !ft_strncmp(ms.input, "exit", 5))
			break ;
		add_history(ms.input);
		if (init_modules(ms.input, &ms) == SUCCESS)
		{
			parse_inputs(&ms.mods, &ms);
			print_inputs(&ms.mods);
			//execute_children(&ms);
			//execute_test(&ms);
			// wait_children(&ms);
			execute_children(&ms);
			wait_children(&ms);
		}
		free_runtime(&ms);
	}
	free_exit(&ms);
	return (ms.excode);
}
