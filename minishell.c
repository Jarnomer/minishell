/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:23 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/19 18:35:59 by jmertane         ###   ########.fr       */
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
		if (!ms.input)
		{
			ft_putendl_fd("exit", STDOUT);
			break ;
		}
		if (ms.input && *ms.input)
			add_history (ms.input);
		if (!init_modules(ms.input, &ms))
		{
			parse_inputs(&ms.mods, &ms);
			execute_children(&ms);
			wait_children(&ms);
		}
		free_runtime(&ms);
	}
	free_exit(&ms);
	return (ms.excode);
}
