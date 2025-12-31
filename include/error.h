/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jankku <jankku@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by jankku            #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by jankku           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define C_BOLD_RED			"\033[1;31m"
# define C_YELLOW			"\033[0;33m"
# define C_RESET			"\033[0m"

# define ERR_PROMPT			"minishell: "

# define ERR_MSG_UNKNOWN	"unknown error"
# define ERR_MSG_MALLOC		"Out of memory"
# define ERR_MSG_SYNTAX		"syntax error"
# define ERR_MSG_CMD		"command not found"
# define ERR_MSG_NOFILE		"No such file or directory"
# define ERR_MSG_PERM		"Permission denied"
# define ERR_MSG_ISDIR		"Is a directory"
# define ERR_MSG_NOTDIR		"Not a directory"
# define ERR_MSG_NUMARG		"numeric argument required"
# define ERR_MSG_TOOMANY	"too many arguments"
# define ERR_MSG_NOTSET		"not set"
# define ERR_MSG_IDFIER		"not a valid identifier"
# define ERR_MSG_COREDUMP	"Quit (core dumped)"
# define ERR_MSG_AMBIG		"ambiguous redirect"

typedef enum e_exit_code
{
	EC_SUCCESS = 0,
	EC_FAILURE = 1,
	EC_SYNTAX = 2,
	EC_NOEXEC = 126,
	EC_NOTFOUND = 127,
	EC_SIGNAL = 128
}	t_exit_code;

typedef enum e_err
{
	ERR_NONE,
	ERR_MALLOC,
	ERR_SYNTAX,
	ERR_CMD_NOT_FOUND,
	ERR_NO_SUCH_FILE,
	ERR_PERMISSION,
	ERR_IS_DIR,
	ERR_NOT_DIR,
	ERR_AMBIG_REDIR
}	t_err;

void	print_error(char *msg);
void	print_error_token(char *token);
void	print_error_cmd(char *cmd, char *msg);
void	print_error_arg(char *cmd, char *arg, char *msg);
void	print_error_errno(char *context);

int		check_cmd_error(const char *path);
char	*err_to_msg(t_err err);

#endif
