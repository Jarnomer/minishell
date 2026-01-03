/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <minishell.h>

typedef enum e_quote_state
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE
}	t_quote_state;

void			expand_ast(t_ast *ast, t_shell *shell);
void			expand_cmd(t_cmd *cmd, t_shell *shell);

char			*expand_word(char *word, t_shell *shell);
char			*expand_var(char *name, t_shell *shell);

char			*get_var_name(const char *str, size_t *len);
t_quote_state	update_quote_state(char c, t_quote_state state);
bool			is_quote_delimiter(char c, t_quote_state state);

char			*append_char(char *result, char c);
char			*append_str(char *result, char *str);
char			*strip_quotes(char *word);

void			expand_wildcards(t_vec *args);
t_vec			get_matching_files(const char *pattern);

#endif
