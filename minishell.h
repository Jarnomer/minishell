/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:35:47 by vkinaret          #+#    #+#             */
/*   Updated: 2024/03/28 20:01:13 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct	s_shell
{
	char	*prompt;
	char	*input;
	char	*output;
	char	**envp;
	int		envp_size;
}				t_shell;

//parser.c
//true parcer uest
char *parse_input(t_shell *ms);

#endif
