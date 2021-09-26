/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:28:13 by jchevet           #+#    #+#             */
/*   Updated: 2021/09/26 14:28:14 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_data(t_data *data)
{
	data->fd1 = 0;
	data->fd2 = 0;
	data->cmd_list = NULL;
	data->nb_of_process = 0;
}

void	set_pipe(t_data *data, int **fd)
{
	int	i;

	i = 0;
	while (i < data->nb_of_process)
	{
		if (pipe(fd[i]) == -1)
			exit_perror("pipe");
		i++;
	}
}
