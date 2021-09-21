//
// Created by Johan Chevet on 6/19/21.
//

#include "../include/pipex.h"

/*Replace stdin by first file fd and stdout by first pipe read fd*/
static void	first_cmd(t_data *data, int **fd)
{
	data->fd1 = open(data->filename1, O_RDWR, S_IRWXU, S_IRWXG);
	if (data->fd1 == -1)
		exit_perror(data->filename1);
	if (dup2(data->fd1, STDIN_FILENO) < 0)
		exit_perror("dup2");
	if (dup2(fd[0][1], STDOUT_FILENO) < 0)
		exit_perror("dup2");
}

/*Replace stdin by previous pipe fd and stdout by last file fd*/
static void	last_cmd(t_data *data, int **fd, int i)
{
	data->fd2 = open(data->filename2, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (data->fd2 == -1)
		exit_perror(data->filename2);
	if (dup2(fd[i - 1][0], STDIN_FILENO) < 0)
		exit_perror("dup2");
	if (dup2(data->fd2, STDOUT_FILENO) < 0)
		exit_perror("dup2");
}

/*Replace stdin by previous pipe fd and stdout by current pipe fd*/
static void	inter_cmd(int **fd, int i)
{
	if (dup2(fd[i - 1][0], STDIN_FILENO) < 0)
		exit_perror("dup2");
	if (dup2(fd[i][1], STDOUT_FILENO) < 0)
		exit_perror("dup2");
}

int	create_child(pid_t pid, int **fd, t_data *data, char **envp)
{
	int		i;
	t_cmd	*cmd_list;

	cmd_list = data->cmd_list;
	i = -1;
	while (++i < data->nb_of_process)
	{
		pid = fork();
		if (pid == 0)
		{
			if (!cmd_list->next) {
				last_cmd(data, fd, i);
			}
			else if (i == 0)
				first_cmd(data, fd);
			else
				inter_cmd(fd, i);
			close_all_fd(data, fd);
			if (execve(cmd_list->path, cmd_list->param, envp) == -1)
				exit_perror(cmd_list->name);
		}
		else if (pid == -1)
			exit_perror("fork");
		cmd_list = cmd_list->next;
	}
	wait(NULL);
	return (0);
}
