/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_cmd	*cmd_new(void)
{
	t_cmd	*cmd;

	cmd = safe_calloc(sizeof(t_cmd));
	cmd->args = vec_new(0);
	cmd->redirs = vec_new(0);
	return (cmd);
}

void	cmd_free(void *ptr)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ptr;
	if (!cmd)
		return ;
	vec_free(&cmd->args, free_str);
	vec_free(&cmd->redirs, redir_free);
	free(cmd);
}

void	cmd_add_arg(t_cmd *cmd, char *arg)
{
	vec_push(&cmd->args, arg);
}
