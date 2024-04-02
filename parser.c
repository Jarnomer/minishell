#include "minishell.h"

static void	append_infile(t_parser **lst, t_parser *new)
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

static char	*next_quote(char *input, char c)
{
	while (*input && *input != c)
		input++;
	return (++input);
}

static char	*find_breakpoint(char *input, char c)
{
	int	quotes;

	quotes = 0;
	while (*input && !ft_isspace(*input))
	{
		if (*input == c && !ft_isspace(*input))
			quotes++;
		input++;
	}
	if (quotes == 1)
		return (next_quote(input, c));
	else
		return (input);
}

char	*format_indirect(char *argv, char c, t_module *mod, t_shell *ms)
{
	t_parser	*new;
	char		*temp;

	while (ft_isspace(*argv))
		argv++;
	temp = find_breakpoint(argv, c);
	new = safe_calloc(sizeof(t_parser), ms);
	safe_substr(&new->content, argv, temp, ms);
	append_infile(&mod->infiles, new);
	return (temp + 1);
}

char	assign_delimiter(char *argv)
{
	char	*sngl;
	char	*dpbl;

	sngl = ft_strchr(argv, '\'');
	dpbl = ft_strchr(argv, '\"');
	if ((sngl && dpbl) && (sngl > dpbl))
		return ('\"');
	else if (sngl && dpbl)
		return ('\'');
	else if (dpbl)
		return ('\"');
	else if (sngl)
		return ('\'');
	else
		return (' ');
}

char	*handle_indirect(char *input, t_module *mod, t_shell *ms)
{
	char	delim;

	if (*(input + 1) == '<')
	{
		input += 2;
		delim = assign_delimiter(input);
		input = format_indirect(input, delim, mod, ms);
	}
	else
	{
		input += 1;
		delim = assign_delimiter(input);
		input = format_indirect(input, delim, mod, ms);
	}
	return (input);
}

void	parse_inputs(t_module **lst, t_shell *ms)
{
	t_module	*mod;
	char		*input;

	mod = *lst;
	while (mod)
	{
		input = mod->input;
		while (ft_strchr(input, '<'))
			input = handle_indirect(input, mod, ms);
		mod = mod->next;
	}
}
