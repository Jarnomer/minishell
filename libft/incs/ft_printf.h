/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:57:14 by jmertane          #+#    #+#             */
/*   Updated: 2024/02/08 17:28:49 by jmertane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# define HEXUPP 	"0123456789ABCDEF"
# define HEXLOW 	"0123456789abcdef"
# define SPECS	 	"cspdiuxX%"

typedef struct s_print
{
	int		result;
	int		length;
}	t_print;

int		ft_printf(const char *format, ...);
void	format_chr(t_print *output, int chr);
void	format_str(t_print *output, char *str);
void	format_int(t_print *output, long val);
void	format_hex(t_print *output, unsigned long hex, char spec);

#endif
