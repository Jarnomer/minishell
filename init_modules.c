#include "minishell.h"

static int	command_count(t_module *mod)
{
	int	len;

	len = 0;
	while (mod)
	{
		mod = mod->next;
		++len;
	}
	return (len);
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

	if (invalid_syntax(input, '|', ms))
		return ;
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
		if (invalid_syntax(mod->input, '<', ms)
			|| invalid_syntax(mod->input, '>', ms))
			return ;
		input = temp + 1;
	}
	ms->cmds = command_count(ms->mods);
	ms->pids = safe_calloc(ms->cmds * sizeof(pid_t), ms);
}
