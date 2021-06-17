/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:39:52 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/03 09:13:23 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*ptrstr;

	ptrstr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptrstr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
