/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sig.h>

/*
** Single global variable for signal number
*/
volatile sig_atomic_t	g_signal = 0;

/*
** Handler for SIGINT in interactive mode (ctrl-C at prompt)
** Clears current line and displays new prompt
*/
static void	handle_sigint_interactive(int sig)
{
	g_signal = sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
** Interactive mode: ctrl-C shows new prompt, ctrl-\ ignored
** Used when waiting for user input at readline prompt
*/
void	setup_signals_interactive(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint_interactive;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

/*
** Child process: restore default signal behavior
** Children should terminate normally on signals
*/
void	setup_signals_child(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/*
** Parent during waitpid: ignore signals
** Prevents parent from being interrupted while waiting
*/
void	setup_signals_ignore(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
