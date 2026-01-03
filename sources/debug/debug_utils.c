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

void	print_debug_header(const char *title, const char *input)
{
	printf("\n╔══════════════════════════════════════════════════════════╗\n");
	printf("║ %s\n", title);
	printf("╠══════════════════════════════════════════════════════════╣\n");
	printf("║ Input: %s\n", input);
	printf("╠══════════════════════════════════════════════════════════╣\n");
}

void	print_debug_footer(void)
{
	printf("╚══════════════════════════════════════════════════════════╝\n");
}

void	print_debug_indent(int depth)
{
	printf("║ ");
	while (depth-- > 0)
		printf("  ");
}
