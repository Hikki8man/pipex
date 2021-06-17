/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:56:19 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/03 09:13:08 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*sptr;

	sptr = (unsigned char *)s;
	i = -1;
	while (++i < n)
	{
		if (sptr[i] == (unsigned char)c)
			return (sptr + i);
	}
	return (0);
}
