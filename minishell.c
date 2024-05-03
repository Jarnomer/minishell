/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:23 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/27 15:51:05 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_eof(t_shell *ms)
{
	ft_putendl_fd("exit", STDOUT);
	free_exit(ms);
	return (0);
}

static void	is_sigint(t_shell *ms)
{
	g_signal = 0;
	ms->excode = 1;
}

int	main(void)
{
	t_shell	ms;

	init_shell(&ms);
	while (true)
	{
		init_signals(0);
		ms.input = readline(ms.prompt);
		if (g_signal == SIGINT)
			is_sigint(&ms);
		if (!ms.input)
			return (is_eof(&ms));
		if (ms.input && *ms.input)
			add_history (ms.input);
		if (!init_modules(ms.input, &ms))
		{
			parse_modules(&ms.mods, &ms);
			execute_children(&ms);
			wait_children(&ms);
		}
		if (g_signal == SIGINT)
			is_sigint(&ms);
		free_runtime(&ms);
	}
	free_exit(&ms);
	return (ms.excode);
}
