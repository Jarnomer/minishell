/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:36:13 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/08 16:18:27 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_logger(char *msg1, char *msg2, char *msg3, t_shell *ms)
{
	char	*message;

	if (!msg1 && !msg2 && !msg3)
		return ;
	safe_strdup(&message, ms->prompt, ms);
	*ft_strchr(message, DOLLAR) = ':';
	safe_strjoin(&message, message, BR, ms);
	safe_strjoin(&message, message, msg1, ms);
	safe_strjoin(&message, message, msg2, ms);
	safe_strjoin(&message, message, T, ms);
	safe_strjoin(&message, message, Y, ms);
	safe_strjoin(&message, message, msg3, ms);
	safe_strjoin(&message, message, T, ms);
	ft_putendl_fd(message, STDERR_FILENO);
	free(message);
}

void	error_fatal(int errcode, char *errmsg, t_shell *ms)
{
	if (errmsg != NULL)
		perror(errmsg);
	if (ms->index != 0)
		wait_children(ms);
	error_exit(errcode, NULL, NULL, ms);
}

void	error_exit(int errcode, char *msg1, char *msg2, t_shell *ms)
{
	if (msg1 != NULL && msg2 != NULL)
		error_logger(msg1, ": ", msg2, ms);
	free_exit(ms);
	exit(errcode);
}
