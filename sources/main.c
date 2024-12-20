/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:32:23 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/17 16:03:42 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_signal = 0;

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
	exit(ms->exitcode);
}

static void	hook_sigint(t_shell *ms)
{
	if (g_signal != SIGINT)
		return ;
	g_signal = NOERROR;
	ms->exitcode = 1;
}

int	main(void)
{
	t_shell	ms;

	init_shell(&ms);
	while (true)
	{
		init_signals(SIG_PARENT);
		ms.input = readline(ms.prompt);
		hook_sigint(&ms);
		if (!ms.input)
			exit_shell(&ms);
		else if (*ms.input)
			add_history(ms.input);
		if (!init_modules(ms.input, &ms))
			execute_shell(&ms);
		hook_sigint(&ms);
		free_runtime(&ms);
	}
	free_exit(&ms);
	return (ms.exitcode);
}
