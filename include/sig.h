/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <minishell.h>
# include <signal.h>

# define SIG_EXITCODE 130

/*
** Global variable for signal
** Stores the signal number received (0 if none)
*/
extern volatile sig_atomic_t	g_signal;

void	setup_signals_interactive(void);
void	setup_signals_child(void);
void	setup_signals_ignore(void);

int		get_exit_status(int status);
int		check_signal_received(void);
void	reset_signal(void);

#endif