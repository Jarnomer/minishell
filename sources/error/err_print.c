/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <string.h>

/*
** Output: minishell: syntax error: <msg>
** Colors: NORMAL     BOLD_RED      YELLOW
*/
void	print_error(char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s%ssyntax error: %s%s%s\n",
		ERR_PROMPT, C_BOLD_RED, C_YELLOW, msg, C_RESET);
}

/*
** Output: minishell: syntax error near unexpected token `<tok>'
** Colors: NORMAL     BOLD_RED                           YELLOW
*/
void	print_error_token(char *token)
{
	if (!token)
		token = "newline";
	ft_dprintf(STDERR_FILENO,
		"%s%ssyntax error near unexpected token %s`%s'%s\n",
		ERR_PROMPT, C_BOLD_RED, C_YELLOW, token, C_RESET);
}

/*
** Output: minishell: <cmd>: <msg>
** Colors: NORMAL     BOLD_RED YELLOW
*/
void	print_error_cmd(char *cmd, char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s%s%s: %s%s%s\n",
		ERR_PROMPT, C_BOLD_RED, cmd, C_YELLOW, msg, C_RESET);
}

/*
** Output: minishell: <cmd>: <arg>: <msg>
** Colors: NORMAL     BOLD_RED  YELLOW  YELLOW
*/
void	print_error_arg(char *cmd, char *arg, char *msg)
{
	ft_dprintf(STDERR_FILENO, "%s%s%s: %s%s: %s%s\n",
		ERR_PROMPT, C_BOLD_RED, cmd, C_YELLOW, arg, msg, C_RESET);
}

/*
** Output: minishell: <context>: <strerror(errno)>
** Colors: NORMAL     BOLD_RED   YELLOW
** Uses errno to get system error message
*/
void	print_error_errno(char *context)
{
	ft_dprintf(STDERR_FILENO, "%s%s%s: %s%s%s\n",
		ERR_PROMPT, C_BOLD_RED, context, C_YELLOW, strerror(errno), C_RESET);
}
