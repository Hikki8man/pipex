/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:33:40 by jchevet           #+#    #+#             */
/*   Updated: 2020/11/24 14:33:57 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*pdest;
	char	*psrc;

	pdest = (char *)dest;
	psrc = (char *)src;
	i = 0;
	if (dest < src)
	{
		while (i < n)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	else if (dest > src)
	{
		while (n--)
			pdest[n] = psrc[n];
	}
	return (dest);
}
