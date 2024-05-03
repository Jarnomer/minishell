/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:23 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/03 18:03:41 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	execute_shell(t_shell *ms)
{
	parse_modules(&ms->mods, ms);
	execute_children(ms);
	wait_children(ms);
}

static inline void	exit_shell(t_shell *ms)
{
	ft_putendl_fd("exit", STDOUT);
	free_exit(ms);
	exit(ms->excode);
}

static inline void	reset_sigint(t_shell *ms)
{
	g_sigint = false;
	ms->excode = 1;
}

int	main(void)
{
	t_shell	ms;

	init_shell(&ms);
	while (true)
	{
		init_signals(&ms);
		ms.input = readline(ms.prompt);
		if (g_sigint == true)
			reset_sigint(&ms);
		else if (!ms.input)
			exit_shell(&ms);
		else if (*ms.input)
			add_history(ms.input);
		if (!init_modules(ms.input, &ms))
			execute_shell(&ms);
		free_runtime(&ms);
	}
	free_exit(&ms);
	return (ms.excode);
}
