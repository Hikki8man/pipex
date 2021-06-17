/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:38:51 by jchevet           #+#    #+#             */
/*   Updated: 2020/11/25 09:47:56 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int	i;
	char			*ptrdest;
	char			*ptrsrc;

	i = 0;
	ptrdest = (char *)dest;
	ptrsrc = (char *)src;
	while (i < n)
	{
		ptrdest[i] = ptrsrc[i];
		if (ptrdest[i] == (char)c)
			return (dest + (i + 1));
		i++;
	}
	return (0);
}
