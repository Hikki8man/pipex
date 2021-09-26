/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:27:27 by jchevet           #+#    #+#             */
/*   Updated: 2021/09/26 14:27:29 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	**malloc_pipes(int ac, t_data *data)
{
	int	**fd;
	int	i;

	i = 0;
	data->nb_of_process += ac - 3;
	fd = ft_calloc(data->nb_of_process + 1, sizeof(int *));
	if (fd == NULL)
		return (NULL);
	while (i < data->nb_of_process)
	{
		fd[i] = ft_calloc(2, sizeof(int));
		if (fd[i] == NULL)
		{
			ft_free_int_tab(fd);
			return (NULL);
		}
		i++;
	}
	return (fd);
}
