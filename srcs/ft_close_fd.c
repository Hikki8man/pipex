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

void	close_all_fd(t_data *data, int **fd)
{
	int	i;

	i = 0;
	if (data->fd1 > 0)
		close_perror(data->fd1, "close file 1");
	if (data->fd2 > 0)
		close_perror(data->fd2, "close file 2");
	while (fd[i])
	{
		close_perror(fd[i][0], "close pipe 0");
		close_perror(fd[i][1], "close pipe 1");
		i++;
	}
}

void	close_perror(int fd, char *name)
{
	if (close(fd) == -1)
		exit_perror(name);
}
