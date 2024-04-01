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

// static void	append_argument(t_parser **lst, t_parser *new)
// {
// 	t_parser	*temp;

// 	if (!*lst)
// 		*lst = new;
// 	else
// 	{
// 		temp = *lst;
// 		while (temp->next)
// 			temp = temp->next;
// 		temp->next = new;
// 	}
// }

// static char	*next_quote(char *input, char c)
// {
// 	if (!*input)
// 	{
// 		perror("syntax error!");
// 		exit(5);
// 	}
// 	while (*input && *input != c)
// 		input++;
// 	if (!*input)
// 	{
// 		perror("syntax error!");
// 		exit(5);
// 	}
// 	return (++input);
// }

// static char	*next_break(char *input, char c)
// {
// 	int	quotes;

// 	quotes = 0;
// 	if (c != '\'' && c != '\"')
// 		c = ' ';
// 	while (*input && !ft_isspace(*input))
// 	{
// 		if (*input == c && !ft_isspace(*input))
// 			quotes++;
// 		input++;
// 	}
// 	if (quotes == 1)
// 		return (next_quote(input, c));
// 	else
// 		return (input);
// }

// static void	parse_input(char *input, t_module *mod, t_shell *ms)
// {
// 	char		*temp;
// 	t_parser	*new;

// 	while (*input)
// 	{
// 		while (ft_isspace(*input))
// 			input++;
// 		temp = next_break(input, *input);
// 		if (input == temp)
// 			break;
// 		new = safe_calloc(sizeof(t_parser), ms);
// 		safe_substr(&new->content, input, temp, ms);
// 		append_argument(&mod->parse, new);
// 		input = temp;
// 	}
// }

void	parse_inputs(t_module **lst, t_shell *ms)
{
	t_module	*mod;
	t_parser	*temp;

	mod = *lst;
	while (mod)
	{
		temp = mod->parse;
		while (temp)
		{
			if (*temp->content == '\'')
				safe_strtrim(&temp->content, "\'", ms);
			else if (*temp->content == '\"')
				safe_strtrim(&temp->content, "\"", ms);
			temp = temp->next;
		}
		mod = mod->next;
	}
}
