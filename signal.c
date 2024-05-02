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

//handle heredoc exit when given control-C
	//option A. exit heredoc_child
	//option B. save stdin, close stdin to exit heredoc mode
	//option C. use a global variable

//handle control-D: exits with exit printed on cmd line
	//no solution yet

//handle control-D in heredoc: exits heredoc with delimiter printed on cmd line
	//no solution yet

static void	sigint_handler(int sig)
{
	if (sig == SIGINT)
		g_sigint = true;
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
