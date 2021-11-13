/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:26:52 by jchevet           #+#    #+#             */
/*   Updated: 2021/09/26 14:26:53 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/*Replace stdin by first file fd and stdout by first pipe read fd*/
static void	first_cmd(t_data *data)
{
	data->fd1 = open(data->filename1, O_RDWR, S_IRWXU, S_IRWXG);
	if (data->fd1 == -1)
		exit_perror(data->filename1);
	dup2(data->fd1, 0);
	close_perror(data->fd1);
	close_perror(data->pipe[0]);
	dup2(data->pipe[1], STDOUT_FILENO);
	close_perror(data->pipe[1]);
}

/*Replace stdin by previous pipe fd and stdout by last file fd*/
static void	last_cmd(t_data *data)
{
	data->fd2 = open(data->filename2, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (data->fd2 == -1)
		exit_perror(data->filename2);
	dup2(data->pipe[0], STDIN_FILENO);
	close_perror(data->pipe[0]);
	dup2(data->fd2, STDOUT_FILENO);
	close_perror(data->fd2);
	close_perror(data->pipe[1]);
}

/*Replace stdin by previous pipe fd and stdout by current pipe fd*/
static void	inter_cmd(t_data *data)
{
	dup2(data->pipe[0], STDIN_FILENO);
	close_perror(data->pipe[0]);
	dup2(data->pipe[1], STDOUT_FILENO);
	close_perror(data->pipe[1]);
}

static void	exec_cmd(t_data *data, int i, t_cmd *cmd_list, char **envp)
{
	if (i > 0)
	{
		dup2(data->prev_pipe_in, data->pipe[0]);
		close_perror(data->prev_pipe_in);
	}
	if (!cmd_list->next)
		last_cmd(data);
	else if (i == 0)
		first_cmd(data);
	else
		inter_cmd(data);
	data->path_tab = split_env_path(envp);
	get_cmd_path(cmd_list, data);
	if (execve(cmd_list->path, cmd_list->param, envp) == -1)
		exit_perror(cmd_list->name);
}

void	create_child(t_data *data, char **envp)
{
	int		i;
	int		pid;
	t_cmd	*cmd_list;

	cmd_list = data->cmd_list;
	i = -1;
	while (++i < data->nb_of_process)
	{
		pipe(data->pipe);
		pid = fork();
		if (pid == 0)
			exec_cmd(data, i, cmd_list, envp);
		else if (pid == -1)
			exit_perror("fork");
		close_pipes(data, cmd_list);
		cmd_list = cmd_list->next;
	}
	while (wait(NULL) != -1)
		;
}
