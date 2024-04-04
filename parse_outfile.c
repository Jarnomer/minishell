#include "minishell.h"

static void	append_outfile(t_parser **lst, t_parser *new)
{
	t_parser	*temp;

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

static char	*format_outfile(char *argv, char c, t_module *mod, t_shell *ms)
{
	t_parser	*new;
	char		*temp;

	while (ft_isspace(*argv))
		argv++;
	temp = find_breakpoint(argv, c);
	new = safe_calloc(sizeof(t_parser), ms);
	safe_substr(&new->content, argv, temp, ms);
	if (ft_strchr(new->content, c))
		filter_quotes(new->content, c, ms);
	append_outfile(&mod->outfiles, new);
	return (temp);
}

char	*handle_outfile(char *input, int *mode, t_module *mod, t_shell *ms)
{
	char	c;

	if (*(input + 1) == '>')
	{
		input += 2;
		*mode = APPEND;
	}
	else
	{
		input += 1;
		*mode = OUTFILE;
	}
	c = assign_delimiter(input);
	return (format_outfile(input, c, mod, ms));
}
