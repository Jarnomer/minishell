/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:21:01 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/11 13:02:54 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	relink_parser(t_parser *lst, t_parser *head, t_module *mod)
{
	t_parser	*last;

	last = parser_last(head);
	last->next = lst->next;
	if (lst->prev != NULL)
		lst->prev->next = head;
	else
		mod->command = head;
	parser_delone(lst);
}

static t_parser	*parse_expand(t_parser *lst, t_shell *ms)
{
	t_parser	*new;
	t_parser	*head;
	char		*start;
	char		*input;

	head = NULL;
	input = lst->content;
	while (input)
	{
		start = input;
		while (*input && !ft_isspace(*input))
			input++;
		new = safe_calloc(sizeof(t_parser), ms);
		parser_append(&head, new);
		safe_substr(&new->content, start, input, ms);
		while (*input && ft_isspace(*input))
			input++;
		if (!*input)
			break ;
	}
	return (head);
}

void	parse_expands(t_module *mod, t_shell *ms)
{
	t_parser	*new;
	t_parser	*temp;
	char		*content;

	temp = mod->command;
	while (temp)
	{
		content = temp->content;
		if (temp->meta == DOLLAR && ft_hasspace(content))
		{
			new = parse_expand(temp, ms);
			relink_parser(temp, new, mod);
		}
		temp = temp->next;
	}
}
