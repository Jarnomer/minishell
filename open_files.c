#include "minishell.h"

void open_file(t_parser **lst, int mode)
{
	t_parser	*temp;

	temp = *lst;
	while (temp->next)
		temp = temp->next;
	if (mode == -1)
	{
		temp->mode = -1;
		temp->fd = -1;
	}
	else
	{
		temp->mode = mode;
		//open fd with mode
	}
}
