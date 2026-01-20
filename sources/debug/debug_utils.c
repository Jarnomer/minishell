/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 00:00:00 by jmertane          #+#    #+#             */
/*   Updated: 2026/01/01 00:00:00 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <debug.h>

void	print_debug_header(const char *title, const char *extra)
{
	int	i;

	printf("\n%s%s╔", DBG_PURPLE, DBG_BOLD);
	i = -1;
	while (++i < DBG_BOX_WIDTH)
		printf("═");
	printf("╗%s\n", DBG_RESET);
	printf("%s║%s %s%s%s%s", DBG_PURPLE, DBG_RESET,
		DBG_GREEN, DBG_BOLD, title, DBG_RESET);
	if (extra)
		printf(" %s%s%s", DBG_CYAN, extra, DBG_RESET);
	printf("\n");
	print_debug_separator();
}

void	print_debug_separator(void)
{
	int	i;

	printf("%s╠", DBG_PURPLE);
	i = -1;
	while (++i < DBG_BOX_WIDTH)
		printf("═");
	printf("╣%s\n", DBG_RESET);
}

void	print_debug_footer(void)
{
	int	i;

	printf("%s╚", DBG_PURPLE);
	i = -1;
	while (++i < DBG_BOX_WIDTH)
		printf("═");
	printf("╝%s\n", DBG_RESET);
}

void	print_debug_line(const char *content)
{
	printf("%s║%s %s\n", DBG_PURPLE, DBG_RESET, content);
}

void	print_debug_indent(int depth)
{
	printf("%s║%s ", DBG_PURPLE, DBG_RESET);
	while (depth-- > 0)
		printf("  ");
}
