//
// Created by Johan Chevet on 6/19/21.
//

#include "../include/pipex.h"

/*Replace stdin by first file fd and stdout by first pipe read fd*/
static void	first_cmd(t_data *data, int **fd)
{
	if (dup2(data->fd1, STDIN_FILENO) < 0)
		exit_perror("dup2");
	if (dup2(fd[0][1], STDOUT_FILENO) < 0)
		exit_perror("dup2");
}

/*Replace stdin by previous pipe fd and stdout by last file fd*/
static void	last_cmd(t_data *data, int **fd, int i)
{
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

int	create_child(int pid, int **fd, t_data *data, char **envp)
{
	int		i;
	t_cmd	*cmd_list;

	cmd_list = data->cmd_list;
	int pid1;
	i = -1;
	while (++i < data->nb_of_process)
	{
		pid = fork();
		pid1 = getpid();
//		ft_printf("pid %d | pid1 %d | i %d | nb process %d\n", pid, pid1, i, data->nb_of_process);
//		pid = -1;
		if (pid == 0)
		{
			if (i == 0)
				first_cmd(data, fd);
			else if (!cmd_list->next)
				last_cmd(data, fd, i);
			else
				inter_cmd(fd, i);
			close_all_fd(data, fd);
			if (execve(cmd_list->path, cmd_list->param, envp) == -1)
				exit_perror("execve pid");
		}
		else if (pid == -1)
		{
			perror("fork");
			return (-1);
		}
		cmd_list = cmd_list->next;
	}
	return (0);
}
