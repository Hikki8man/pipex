/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 10:13:41 by jchevet           #+#    #+#             */
/*   Updated: 2020/11/30 13:00:56 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

typedef struct s_doubleint
{
	int	len;
	int	size;
}t_intx2;

int	ft_issep(char s, char c)
{
	return (s == c);
}

static int	ft_strcount(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && ft_issep(s[i], c))
		i++;
	if (s[i] == '\0')
		return (count);
	while (s[i])
	{
		if (ft_issep(s[i], c) && !ft_issep(s[i + 1], c) && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count + 1);
}

static int	ft_wordlen(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && !ft_issep(s[i], c))
		i++;
	return (i);
}

static int	ft_calloc_check(char **tomalloc, int count, int size)
{
	*tomalloc = ft_calloc(count, size);
	if (!*tomalloc)
		return (-1);
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**t;
	int		i;
	t_intx2	tinfo;

	if (!s)
		return (NULL);
	tinfo.size = ft_strcount((char *)s, c);
	t = (char **)ft_calloc(tinfo.size + 1, sizeof(char *));
	if (!t)
		return (NULL);
	i = -1;
	while (++i < tinfo.size)
	{
		while (ft_issep(*s, c))
			s++;
		tinfo.len = ft_wordlen((char *)s, c);
		if (ft_calloc_check(&t[i], tinfo.len + 1, sizeof(char)) == -1)
		{
			ft_free_tab(t, i);
			return (NULL);
		}
		ft_strlcpy(t[i], s, tinfo.len + 1);
		s += tinfo.len;
	}
	return (t);
}
