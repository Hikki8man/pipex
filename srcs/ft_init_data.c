//
// Created by Johan Chevet on 6/19/21.
//

#include "../include/pipex.h"

void	init_data(t_data *data)
{
	data->fd1 = 0;
	data->fd2 = 0;
	data->cmd_list = NULL;
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
