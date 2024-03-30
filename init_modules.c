#include "minishell.h"

// static int	count_arguments(t_parser *lst)
// {
// 	int	len;

// 	len = 0;
// 	while (lst)
// 	{
// 		lst = lst->next;
// 		++len;
// 	}
// 	return (len);
// }

static void	append_argument(t_parser **lst, t_parser *new)
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








































static inline int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static char	*next_quote(char *input, char c)
{
	if (!*input)
		exit (5); // this means that user just inserted quote at the end -> error
	while (*input && *input != c)
		input++;
	if (!*input)
		exit (5); // this means that user didn't insert closing quote -> error
	return (++input);
}

static char	*breakpoint(char *input, char c)
{
	int	quotes;

	quotes = 0;
	if (c != '\'' && c != '\"')
		c = ' ';
	while (*input && !ft_isspace(*input))
	{
		if (*input == c && c != ' ')
			quotes++;
		input++;
	}
	if (quotes == 1)
		return (next_quote(input, c));
	else
		return (input);
}

static void	parse_input(char *input, t_module *mod)
{
	char		*temp;
	t_parser	*new;

	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		temp = breakpoint(input, *input);
		if (input == temp)
			break;
		new = ft_calloc(1, sizeof(t_parser));
		if (!new)
			perror("Malloc failed!");
		new->content = ft_substr(input, 0, temp - input);
		if (!new->content)
			perror("Malloc failed!");
		append_argument(&mod->parse, new);
		input = temp;
	}
}

void init_modules(char *input, t_shell *ms)
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
		mod = ft_calloc(1, sizeof(t_module));
		if (!mod)
			perror("Malloc failed!");
		mod->input = ft_substr(input, 0, temp - input);
		if (!mod->input)
			perror("Malloc failed!");
		parse_input(mod->input, mod);
		append_module(&ms->mods, mod);
		input = temp + 1;
	}
}
