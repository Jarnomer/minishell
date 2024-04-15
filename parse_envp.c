/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:26:07 by jmertane          #+#    #+#             */
/*   Updated: 2024/04/15 16:39:37 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*envp_exists(t_shell *ms, char *name)
{
	char	*temp;
	int		len;
	int		i;

	i = 0;
	temp = NULL;
	safe_strjoin(&temp, name, "=", ms);
	len = ft_strlen(temp);
	while (ms->envp[i] && !ft_strnstr(ms->envp[i], temp, len))
		i++;
	free_single(&temp);
	if (ms->envp[i] != NULL)
		return (ms->envp[i] + len);
	return (NULL);
}

static char	*ft_isenvp(char *input)
{
	if (!input)
		return (NULL);
	while (*input && *input != '$')
		input++;
	if (!*input)
		return (NULL);
	return (input);
}

static int	expand_found(t_parser *node)
{
	while (node)
	{
		if (ft_isenvp(node->content))
			return (SUCCESS);
		node = node->next;
	}
	return (FAILURE);
}

static void	expand_envps(t_parser **lst, t_shell *ms)
{
	t_parser	*node;
	t_parser	*next;
	char		*argv;

	node = *lst;
	while (node)
	{
		while (node && !ft_isenvp(node->content))
			node = node->next;
		if (node)
		{
			next = node->next;
			argv = ft_isenvp(node->content);
			argv = envp_exists(ms, argv + 1);
			node = next;
		}
	}
}

void	parse_envp(t_module *mod, t_shell *ms)
{
	if (!expand_found(mod->command))
		expand_envps(&mod->command, ms);
	if (!expand_found(mod->infiles))
		expand_envps(&mod->infiles, ms);
	if (!expand_found(mod->outfiles))
		expand_envps(&mod->outfiles, ms);
}

// static void	parser_add_front(t_parser **lst, t_parser *new)
// {
// 	if (!lst || !new)
// 		return ;
// 	new->next = *lst;
// 	*lst = new;
// }
