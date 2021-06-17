/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 15:00:09 by jchevet           #+#    #+#             */
/*   Updated: 2020/11/28 07:01:25 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

int	ft_isset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_len(char *start, char *end)
{
	int		i;

	i = 0;
	if (start == end)
		return (1);
	while (start <= end)
	{
		start++;
		i++;
	}
	return (i + 1);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*s;
	char	*start;
	char	*end;
	int		i;

	if (!s1)
		return (NULL);
	while (*s1 && ft_isset(*s1, set))
		s1++;
	start = (char *)s1;
	end = start;
	while (*s1)
	{
		if (!ft_isset(*s1, set))
			end = (char *)s1;
		s1++;
	}
	s = malloc(sizeof(char) * (ft_len(start, end)));
	if (!s)
		return (NULL);
	i = 0;
	while (start <= end && *start != '\0')
		s[i++] = *start++;
	s[i] = '\0';
	return (s);
}
