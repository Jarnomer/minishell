/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:01:06 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/18 15:58:31 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	g_sigint = false;

static void	sigint_handler(int sig)
{
	if (sig == SIGINT)
		g_sigint = true;
	if (g_heredoc == true)
	{
		close(STDIN);
		return ;
	}
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(t_shell *ms)
{
	struct termios	term;

	if (!ms)
		return ;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDERR_FILENO, TCSANOW, &term);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
