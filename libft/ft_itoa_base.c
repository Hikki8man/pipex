/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:51:26 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/19 17:51:26 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

int	ft_alength(int n, int *sign, int base_len, unsigned int *nb)
{
	int				len;
	unsigned int	tmp;

	*nb = (unsigned int)n;
	*sign = 0;
	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		*nb = (unsigned int) - n;
		*sign = 1;
	}
	tmp = *nb;
	while (tmp > 0)
	{
		tmp /= base_len;
		len++;
	}
	return (len += *sign);
}

char	*ft_itoa_base(int n, char *base)
{
	unsigned int	nb;
	char			*to_ret;
	int				sign;
	int				size;
	int				base_len;

	base_len = ft_strlen(base);
	size = ft_alength(n, &sign, base_len, &nb);
	to_ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!to_ret)
		return (NULL);
	to_ret[size] = '\0';
	if (n < 0)
		to_ret[0] = '-';
	while (--size >= sign)
	{
		to_ret[size] = base[nb % base_len];
		nb /= base_len;
	}
	return (to_ret);
}
