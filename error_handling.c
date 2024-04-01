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
	close_fds(&ms->fds);
	self_destruct(ms);
	exit(errcode);
}
