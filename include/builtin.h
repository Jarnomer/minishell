/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <shell.h>

typedef struct s_builtin
{
	const char	*name;
	int			(*func)(t_vec *args, t_shell *shell);
}	t_builtin;

bool	is_builtin(const char *cmd);
int		run_builtin(t_cmd *cmd, t_shell *shell);

int		builtin_echo(t_vec *args, t_shell *shell);
int		builtin_cd(t_vec *args, t_shell *shell);
int		builtin_pwd(t_vec *args, t_shell *shell);
int		builtin_export(t_vec *args, t_shell *shell);
int		builtin_unset(t_vec *args, t_shell *shell);
int		builtin_env(t_vec *args, t_shell *shell);
int		builtin_exit(t_vec *args, t_shell *shell);

void	sort_str_arr(char **arr, size_t len);
bool	is_valid_identifier(const char *name, size_t len);
bool	is_numeric(const char *str);
bool	is_overflow(const char *str);

#endif
