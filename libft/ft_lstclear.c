/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 05:01:44 by jchevet           #+#    #+#             */
/*   Updated: 2020/11/30 12:33:34 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*list;

	if (*lst)
	{
		list = *lst;
		*lst = NULL;
		while (list)
		{
			tmp = list->next;
			del(list->content);
			free(list);
			list = tmp;
		}
	}
}
