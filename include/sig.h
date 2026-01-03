/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include <shell.h>

# define SIG_EXITCODE 130

extern volatile sig_atomic_t	g_signal;

void	setup_signals_interactive(void);
void	setup_signals_child(void);
void	setup_signals_ignore(void);

int		get_exit_status(int status);
int		check_signal_received(void);
void	reset_signal(void);

#endif