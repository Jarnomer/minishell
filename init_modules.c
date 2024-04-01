#include "minishell.h"

static inline int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static void	append_module(t_module **lst, t_module *new)
{
	t_module	*temp;

	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void	init_modules(char *input, t_shell *ms)
{
	char		*temp;
	t_module	*mod;

	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		temp = ft_strchr(input, '|');
		if (!temp)
			temp = input + ft_strlen(input);
		mod = safe_calloc(sizeof(t_module), ms);
		safe_substr(&mod->input, input, temp, ms);
		append_module(&ms->mods, mod);
		if (invalid_syntax(input, mod, ms))
			break ;
		input = temp + 1;
	}
}
