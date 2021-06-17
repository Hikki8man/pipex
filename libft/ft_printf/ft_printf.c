/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:55:15 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/19 17:53:52 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print(char c, va_list varlist, t_flags *flags, int *char_printed)
{
	int	check;

	check = 0;
	flags->conv = c;
	if (c == 'd' || c == 'i')
		check = print_int(varlist, flags, char_printed);
	else if (c == 's')
		check = print_str(varlist, flags, char_printed);
	else if (c == 'c')
		check = print_char(varlist, flags, char_printed);
	else if (c == 'u')
		check = print_uint(varlist, flags, char_printed);
	else if (c == 'x' || c == 'X')
		check = print_hex(varlist, flags, char_printed);
	else if (c == 'p')
		check = print_p(varlist, flags, char_printed);
	else if (c == '%')
		check = print_percent(flags, char_printed);
	return (check);
}

int	ft_printf(const char *str, ...)
{
	int		char_printed;
	t_flags	flags;
	va_list	var_list;

	if (!str)
		return (-1);
	char_printed = 0;
	va_start(var_list, str);
	while (*str)
	{
		flags = init_struct();
		if (is_valid(&str, &flags, var_list))
		{
			if (print(*str++, var_list, &flags, &char_printed) == -1)
				return (-1);
		}
		else if (*str == '%' && *(str + 1) == '\0')
			str++;
		else
			char_printed += write(1, str++, 1);
	}
	va_end(var_list);
	return (char_printed);
}
