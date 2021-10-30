/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_prec_width.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:48:15 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/19 17:48:15 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	int_len(int nb)
{
	int	i;

	i = 0;
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int	get_precision(char *str_flags, t_flags *flags, va_list varlist)
{
	if (*str_flags == '*')
	{
		flags->precision = va_arg(varlist, int);
		if (flags->precision < 0)
			flags->precision = -1;
		return (2);
	}
	flags->precision = ft_atoi(str_flags);
	return (int_len(flags->precision) + 1);
}

int	get_width(char *str_flag, t_flags *flags, va_list varlist)
{
	if (*str_flag == '*')
	{
		flags->width = va_arg(varlist, int);
		if (flags->width < 0)
		{
			flags->width *= -1;
			flags->minus = 1;
		}
		return (0);
	}
	flags->width = ft_atoi(str_flag);
	return (int_len(flags->width) - 1);
}
