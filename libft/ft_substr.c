/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:19:10 by jchevet           #+#    #+#             */
/*   Updated: 2020/11/30 17:04:58 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	size_t			l;

	l = ft_strlen(s);
	if (start > l)
		len = 0;
	else if (len > l)
		len = l;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!s || !str)
		return (NULL);
	i = 0;
	if (start <= ft_strlen(s))
	{
		while (s[i + start] && i < len)
		{
			str[i] = s[i + start];
			i++;
		}
	}
	return (str);
}
