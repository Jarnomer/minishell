#include "minishell.h"

void	close_fds(t_descriptors **fds)
{
	if (!(*fds))
		return ;
	if ((*fds)->pipe[WR_END] != -1)
		close((*fds)->pipe[WR_END]);
	if ((*fds)->pipe[RD_END] != -1)
		close((*fds)->pipe[RD_END]);
	if ((*fds)->in != -1)
		close((*fds)->in);
	if ((*fds)->out != -1)
		close((*fds)->out);
}
