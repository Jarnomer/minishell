#include "minishell.h"

int	ft_issyntax(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}
