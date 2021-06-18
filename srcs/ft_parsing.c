#include "../include/pipex.h"

void openfiles(char **av, int ac, t_data *data)
{
	data->fd1 = open(av[1], O_RDWR, S_IRWXU, S_IRWXG);
	if (data->fd1 == -1)
		exit_perror("open");
	data->fd2 = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (data->fd2 == -1)
		exit_perror("open");
}