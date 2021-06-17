/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:52:53 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/19 17:52:56 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	print_percent(t_flags *flags, int *char_printed)
{
	flags->width -= 1;
	if (!flags->minus)
		*char_printed += print_field(flags);
	*char_printed += write(1, "%", 1);
	if (flags->minus)
		*char_printed += print_field(flags);
	return (1);
}
