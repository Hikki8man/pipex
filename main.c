#include <stdio.h>
#include <unistd.h>
#include "libft/include/libft.h"
#include <fcntl.h>
#include <errno.h>
#define TRUE 1
#define FALSE 0

//fd[0] = READ
//fd[1] = WRITE


typedef struct s_cmd
{
	char	*name;
	char	*path;
	char	**param;
	struct s_cmd *next;
}t_cmd;

typedef struct s_data
{
	int		fd1;
	int		fd2;
	int 	nb_of_process;
	t_cmd	*cmd_list;
}t_data;

void	init_data(t_data *data)
{
	data->fd1 = 0;
	data->fd2 = 0;
	data->cmd_list = NULL;
}

void exit_perror(char *name)
{
	perror(name);
	exit(EXIT_FAILURE);
}

void close_perror(int fd, char *name)
{
	if (close(fd) == -1)
		exit_perror(name);
}

t_cmd	*cmd_lst_last(t_cmd *cmd_l)
{
	while (cmd_l && cmd_l->next)
		cmd_l = cmd_l->next;
	return (cmd_l);
}

t_cmd *new_cmd(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->param = NULL;
	cmd->name = 0;
	cmd->path = NULL;
	cmd->next = NULL;
	return (cmd);
}
void	add_back(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (*cmd_list == NULL)
		*cmd_list = new_cmd;
	else
	{
		last = cmd_lst_last(*cmd_list);
		last->next = new_cmd;
	}
}

void	add_slash_to_path(char **path_tab)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path_tab[i])
	{
		tmp = ft_strjoin(path_tab[i], "/");
		if (!tmp)
			exit(-1);
		free(path_tab[i]);
		path_tab[i] = tmp;
		i++;
	}
}

char	**split_env_path(char **envp)
{
	int	i;
	char **paths_tab;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	envp[i] += 5;
	paths_tab = ft_split(envp[i], ':');
	add_slash_to_path(paths_tab);
	return (paths_tab);
}

int 	nb_of_param(char **param)
{
	int	i;

	i = 0;
	while (param[i])
		i++;
	return (i);
}

void	get_cmd(int ac, char **av, t_cmd **cmd_l)
{
	t_cmd *cmd;
	int i;

	i = 2;
	while (i < ac - 1)
	{
		cmd = new_cmd();
		if (!cmd)
			exit_perror("new_cmd");
		cmd->param = ft_split(av[i], ' ');
		cmd->name = *cmd->param;
		add_back(cmd_l, cmd);
		i++;
	}
}

void	free_cmd_list(t_cmd **cmd)
{
	t_cmd *tmp;
	
	while (*cmd)
	{
		tmp = *cmd;
		if ((*cmd)->path)
			free((*cmd)->path);
		ft_free_str_tab((*cmd)->param);
		free(*cmd);
		*cmd = tmp->next;
	}
}

void 	exit_failure(t_cmd **cmd, char **path_tab)
{
//	ft_free_str_tab(path_tab);
//	free_cmd_list(cmd);
	exit(1);
}

void get_cmd_path(t_cmd **cmd_list, char **path_tab)
{
	t_cmd	*tmp;
	int 	i;
	int 	isopen;

	tmp = *cmd_list;
	while (tmp)
	{
		i = 0;
		while (path_tab[i])
		{
			tmp->path = ft_strjoin(path_tab[i], tmp->name);
			if (tmp->path == NULL)
				exit(2);
			isopen = open(tmp->path, O_RDONLY);
			if (isopen != -1)
			{
				close_perror(isopen, "open");
				break ;
			}
			free(tmp->path);
			tmp->path = NULL;
			i++;
		}
		if (tmp->path == NULL) {
			ft_printf("%s: command not found\n", tmp->name);
			exit_failure(cmd_list, path_tab);
		}//cmd not found / valid
		tmp = tmp->next;
	}
	ft_free_str_tab(path_tab);
}

void openfiles(char **av, int ac, t_data *data)
{
	data->fd1 = open(av[1], O_RDWR, S_IRWXU, S_IRWXG);
	if (data->fd1 == -1)
		exit_perror("open");
	data->fd2 = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, S_IRWXG);
	if (data->fd2 == -1)
		exit_perror("open");

}

void child1(int pid, int *fd, t_data *data, char **envp)
{
	pid = fork();
	if (pid == -1)
	{
		close_perror(fd[0], "close pipe 0");
		close_perror(fd[1], "close pipe 1");
		exit_perror("fork");
	}
	if (pid == 0)
	{
		close_perror(fd[0], "close pipe 0");
		dup2(data->fd1, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close_perror(fd[1], "close pipe 1");
		if (execve(data->cmd_list->path, data->cmd_list->param, envp))
			exit_perror("execve pid1");
	}
}

void child2(int pid, int *fd, t_data *data, char **envp)
{
	pid = fork();
	if (pid == -1)
	{
		close_perror(fd[0], "close pipe 0");
		close_perror(fd[1], "close pipe 1");
		exit_perror("fork");
	}
	if (pid == 0)
	{
		close_perror(fd[1], "close pipe 1");
		dup2(fd[0], STDIN_FILENO);
		close_perror(fd[0], "close pipe 0");
		dup2(data->fd2, STDOUT_FILENO);
		data->cmd_list = data->cmd_list->next;
		if (execve(data->cmd_list->path, data->cmd_list->param, envp) == -1)
			exit_perror("execve pid2");
	}
}

void child3(int pid, int *fd, t_data *data, char **envp)
{
	pid = fork();
	if (pid == -1)
	{
		close_perror(fd[0], "close pipe 0");
		close_perror(fd[1], "close pipe 1");
		exit_perror("fork");
	}
	if (pid == 0)
	{
		close_perror(fd[1], "close pipe 1");
		dup2(fd[0], STDIN_FILENO);
		close_perror(fd[0], "close pipe 0");
		dup2(data->fd2, STDOUT_FILENO);
		data->cmd_list = data->cmd_list->next;
		if (execve(data->cmd_list->path, data->cmd_list->param, envp) == -1)
			exit_perror("execve pid2");
	}
}

void close_all_fd(t_data *data, int *fd)
{
	close_perror(data->fd1, "close file 1");
	close_perror(data->fd2, "close file 2");
	close_perror(fd[0], "close pipe 0");
	close_perror(fd[1], "close pipe 1");
}

int main(int argc, char **argv, char **envp)
 {
	int **fd;
	int pid1;
	int pid2;
	char **path_tab;
	t_data data;
	
	data.nb_of_process = argc - 3;
	 fd = malloc(data.nb_of_process * sizeof(int *));
	if (argc == 5)
	{
		if (pipe(fd) == -1)
			exit_perror("pipe");
		init_data(&data);
		openfiles(argv, argc, &data);
		path_tab = split_env_path(envp);
		get_cmd(argc, argv, &data.cmd_list);
		get_cmd_path(&data.cmd_list, path_tab);
		child1(pid1, fd, &data, envp);
		child2(pid2, fd, &data, envp);
		close_all_fd(&data, fd);
		if (waitpid(pid1, NULL, 0) == -1)
			exit_perror("waitpid");
		if (waitpid(pid2, NULL, 0) == -1)
			exit_perror("waitpid");
		free_cmd_list(&data.cmd_list);
		exit(0);
	}
	 exit(-1);
}
