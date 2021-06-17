/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 15:18:22 by jchevet           #+#    #+#             */
/*   Updated: 2020/11/24 15:22:18 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char	*ptr_dest;
	size_t	free_space;

	ptr_dest = dst;
	free_space = dstsize;
	while (*ptr_dest && free_space != 0)
	{
		ptr_dest++;
		free_space--;
	}
	if (free_space == 0)
		return (ft_strlen(src) + dstsize);
	while (*src && free_space > 1)
	{
		*ptr_dest++ = *src++;
		free_space--;
	}
	*ptr_dest = '\0';
	return (ft_strlen(dst) + ft_strlen(src));
}
