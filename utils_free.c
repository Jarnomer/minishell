#include "minishell.h"

void	free_single(char **str)
{
	if (!str || !*str)
		return ;
	free(*str);
	*str = NULL;
}

void	free_douple(char ***arr)
{
	int	i;

	if (!arr || !*arr)
		return ;
	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

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
