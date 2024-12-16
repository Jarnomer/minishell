/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:01:06 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/06 17:58:40 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
		g_signal = SIGINT;
	ft_putchar_fd('\n', STDOUT);
	close(STDIN);
}

static void	sigint_handler(int sig)
{
	if (sig == SIGINT)
		g_signal = SIGINT;
	ft_putchar_fd('\n', STDOUT);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		g_signal = SIGQUIT;
		ft_putstr_fd("Quit: 3", STDOUT);
	}
	ft_putstr_fd("\n", STDOUT);
}

void	init_signals(int mode)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	if (mode == SIG_CHILD)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDERR_FILENO, TCSANOW, &term);
	if (mode == SIG_PARENT)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == SIG_HEREDOC)
	{
		signal(SIGINT, heredoc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == SIG_CHILD)
	{
		signal(SIGINT, sigquit_handler);
		signal(SIGQUIT, sigquit_handler);
	}
}
