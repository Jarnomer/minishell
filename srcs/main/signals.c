/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:01:06 by vkinaret          #+#    #+#             */
/*   Updated: 2024/05/05 15:55:50 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_signal = 0;

static void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
		g_signal = 2;
	ft_putchar_fd('\n', 1);
	close(STDIN);
}

static void	sigint_handler(int sig)
{
	if (sig == SIGINT)
		g_signal = 2;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sigquit_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		g_signal = 3;
		ft_putstr_fd("Quit: 3", 1);
	}
	ft_putstr_fd("\n", 1);
}

void	init_signals(int mode)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
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
