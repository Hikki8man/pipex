/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:26:08 by jchevet           #+#    #+#             */
/*   Updated: 2021/09/26 14:26:40 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	close_perror(int fd)
{
	if (close(fd) == -1)
		perror("close");
}

void	close_pipes(t_data *data, t_cmd *cmd_list)
{
	if (cmd_list->next)
	{
		data->prev_pipe_in = data->pipe[0];
		close_perror(data->pipe[1]);
	}
	else
	{
		close_perror(data->pipe[0]);
		close_perror(data->pipe[1]);
		close_perror(data->prev_pipe_in);
	}
}
