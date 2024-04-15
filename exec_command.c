/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 19:14:32 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/09 19:18:29 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**build_command(t_parser *command, t_shell *ms)
{
	char	**cmd;
	int		i;

	cmd = safe_calloc((parser_length(command) + 1) * sizeof(char *), ms);
	i = 0;
	while (command)
	{
		if (*command->content)
			cmd[i] = command->content;
		command = command->next;
		i++;
	}
	return (cmd);
}

void	execute_command(t_module *mod, t_shell *ms)
{
	char	**cmd;
	char	*exec;

	exec = mod->command->content;
	exec = executable_path(exec, ms);
	cmd = build_command(mod->command, ms);
	execve(exec, cmd, ms->envp);
}
