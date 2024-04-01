#include "minishell.h"

char	**init_environ(void)
{
	extern char	**environ;

	return (environ);
}
