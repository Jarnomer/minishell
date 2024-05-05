/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fmt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:53:31 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 14:19:02 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	format_chr(t_print *output, int chr)
{
	if (ft_putchar_fd(chr, 1) == -1)
		output->length = -1;
	else
		output->length += 1;
}

void	format_str(t_print *output, char *str)
{
	if (!str)
		output->result = ft_putstr_fd("(null)", 1);
	else
		output->result = ft_putstr_fd(str, 1);
	if (output->result == -1)
		output->length = -1;
	else
		output->length += output->result;
}

void	format_int(t_print *output, long val)
{
	output->result = ft_putnbr_fd(val, 1);
	if (output->result == -1)
		output->length = -1;
	else
		output->length += output->result;
}

void	format_hex(t_print *output, unsigned long hex, char spec)
{
	if (hex >= 16)
		format_hex(output, hex / 16, spec);
	if (spec == 'p' && hex < 16)
		format_str(output, "0x");
	if (output->length == -1)
		return ;
	if (spec == 'x' || spec == 'p')
		format_chr(output, HEXLOW[hex %= 16]);
	else
		format_chr(output, HEXUPP[hex %= 16]);
}
