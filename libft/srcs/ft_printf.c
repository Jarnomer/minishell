/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:50 by jmertane          #+#    #+#             */
/*   Updated: 2024/05/05 14:19:07 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	format_spec(t_print *output, va_list args, char spec)
{
	if (spec == '%')
		format_chr(output, '%');
	else if (spec == 'c')
		format_chr(output, va_arg(args, int));
	else if (spec == 's')
		format_str(output, va_arg(args, char *));
	else if (spec == 'i' || spec == 'd')
		format_int(output, va_arg(args, int));
	else if (spec == 'u')
		format_int(output, va_arg(args, unsigned int));
	else if (spec == 'x' || spec == 'X')
		format_hex(output, va_arg(args, unsigned int), spec);
	else if (spec == 'p')
		format_hex(output, va_arg(args, unsigned long), spec);
}

int	ft_printf(const char *format, ...)
{
	t_print	output;
	va_list	args;

	output.length = 0;
	va_start (args, format);
	while (*format)
	{
		output.result = 0;
		if (*format != '%')
			format_chr(&output, *format);
		else if (ft_strchr(SPECS, *(format + 1)))
			format_spec(&output, args, *++format);
		if (output.length == -1 || !*format)
			break ;
		++format;
	}
	va_end (args);
	return (output.length);
}
