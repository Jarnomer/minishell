/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinaret <vkinaret@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:16:29 by vkinaret          #+#    #+#             */
/*   Updated: 2024/04/02 14:16:35 by vkinaret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_logger(char *msg1, char *msg2, char *msg3)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(BR, STDERR_FILENO);
	ft_putstr_fd(msg1, STDERR_FILENO);
	ft_putstr_fd(msg2, STDERR_FILENO);
	ft_putstr_fd(T, STDERR_FILENO);
	ft_putstr_fd(Y, STDERR_FILENO);
	ft_putendl_fd(msg3, STDERR_FILENO);
	ft_putstr_fd(T, STDERR_FILENO);
}

void	exit_error(int errcode, char *errmsg, t_shell *ms)
{
	if (errmsg != NULL)
	{
		error_logger(errmsg, ": ", strerror(errno));
	}
	free_struct(ms);
	exit(errcode);
}

static int	error_occured(int errcode, char *token, t_shell *ms)
{
	error_logger(MSG_SYNX, " ", token);
	ms->excode = errcode;
	return (errcode);
}

static int	invalid_argument(char *input, char c)
{
	int	len;

	if (!input || !*input)
		return (FAILURE);
	len = ft_strlen(input) - 1;
	if (input[0] == c)
		return (FAILURE);
	else if (input[len] == c)
		return (FAILURE);
	else
		return (SUCCESS);
}

int	invalid_syntax(char *input, t_module *mod, t_shell *ms)
{
	if (invalid_argument(input, '|'))
		return (error_occured(ERR_SYNX, "'|'", ms));
	if (invalid_argument(mod->input, '<'))
		return (error_occured(ERR_SYNX, "'<'", ms));
	if (invalid_argument(mod->input, '>'))
		return (error_occured(ERR_SYNX, "'>'", ms));
	return (SUCCESS);
}
