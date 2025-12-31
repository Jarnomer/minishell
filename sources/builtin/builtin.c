/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtin.h>

static const t_builtin	g_builtins[] = {
{"echo", builtin_echo},
{"cd", builtin_cd},
{"pwd", builtin_pwd},
{"export", builtin_export},
{"unset", builtin_unset},
{"env", builtin_env},
{"exit", builtin_exit},
{NULL, NULL}
};

bool	is_builtin(const char *cmd)
{
	size_t	i;

	if (!cmd)
		return (false);
	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(cmd, g_builtins[i].name) == 0)
			return (true);
		i++;
	}
	return (false);
}

static int	run_builtin_cmd(const char *name, t_vec *args, t_shell *shell)
{
	size_t	i;

	i = 0;
	while (g_builtins[i].name)
	{
		if (ft_strcmp(name, g_builtins[i].name) == 0)
			return (g_builtins[i].func(args, shell));
		i++;
	}
	return (EC_FAILURE);
}

int	run_builtin(t_cmd *cmd, t_shell *shell)
{
	char	*name;

	if (!cmd || cmd->args.len == 0)
		return (EC_FAILURE);
	name = vec_get(&cmd->args, 0);
	return (run_builtin_cmd(name, &cmd->args, shell));
}
