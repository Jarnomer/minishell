/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error.h>

void	print_error_token(char *token)
{
	ft_dprintf(STDERR_FILENO,
		"%s%ssyntax error near unexpected token %s`%s'%s\n",
		ERR_PROMPT, C_BOLD_RED, C_YELLOW, token, C_RESET);
}

void	print_error_cmd(char *cmd, char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s%s%s: %s%s%s\n",
		ERR_PROMPT, C_BOLD_RED, cmd, C_YELLOW, msg, C_RESET);
}

void	print_error_arg(char *cmd, char *arg, char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s%s%s: %s%s: %s%s\n",
		ERR_PROMPT, C_BOLD_RED, cmd, C_YELLOW, arg, msg, C_RESET);
}

void	print_error_errno(char *context)
{
	ft_dprintf(STDERR_FILENO, "%s%s%s: %s%s%s\n",
		ERR_PROMPT, C_BOLD_RED, context, C_YELLOW, strerror(errno), C_RESET);
}
