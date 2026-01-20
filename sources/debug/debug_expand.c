/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>

static void	print_expand_header(const char *title)
{
	int		i;

	printf("\n%s%s╔", DBG_PURPLE, DBG_BOLD);
	i = -1;
	while (++i < DBG_BOX_WIDTH)
		printf("═");
	printf("╗%s\n", DBG_RESET);
	printf("%s║%s %s%s%s%s\n", DBG_PURPLE, DBG_RESET,
		DBG_GREEN, DBG_BOLD, title, DBG_RESET);
	print_debug_separator();
}

void	debug_print_expand(t_ast *ast, t_shell *shell)
{
	expand_ast(ast, shell);
	print_expand_header("3. FINAL RESULT");
	debug_print_ast(ast, 0);
	print_debug_footer();
}
