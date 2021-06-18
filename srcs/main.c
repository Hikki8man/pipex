#include "../include/pipex.h"

//fd[0] = READ
//fd[1] = WRITE

void	init_data(t_data *data)
{
	data->fd1 = 0;
	data->fd2 = 0;
	data->cmd_list = NULL;
}

void	ft_free_int_tab(int **t)
{
	int	i;

	i = 0;
	if (t)
	{
		while (t[i])
		{
			free(t[i]);
			i++;
		}
		free(t);
	}
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
	ft_free_str_tab(path_tab);
	free_cmd_list(cmd);
	exit(1);
}

int	command_not_found(char *path, char *name)
{
	if (path == NULL)
	{
		ft_printf("%s: command not found\n", name);
		return (1);
	}
	return (0);
}

int path_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		close_perror(fd, "open");
		return (1);
	}
	return (0);
}

void get_cmd_path(t_cmd **cmd_list, char **path_tab)
{
	t_cmd	*tmp;
	int 	i;

	tmp = *cmd_list;
	while (tmp)
	{
		i = 0;
		while (path_tab[i])
		{
			tmp->path = ft_strjoin(path_tab[i++], tmp->name);
			if (tmp->path == NULL)
				exit(2);// free cmd_list, cmd param**
			if (path_exist(tmp->path) == 1)
				break ;
			free(tmp->path);
			tmp->path = NULL;
		}
		if (command_not_found(tmp->path, tmp->name))
			exit_failure(cmd_list, path_tab);
		tmp = tmp->next;
	}
	ft_free_str_tab(path_tab);
}

void close_all_fd(t_data *data, int **fd)
{
	int	i;

	i = 0;
	close_perror(data->fd1, "close file 1");
	close_perror(data->fd2, "close file 2");
	while (fd[i])
	{
		close_perror(fd[i][0], "close pipe 0");
		close_perror(fd[i][1], "close pipe 1");
		i++;
	}
}

void first_cmd(t_data *data, int **fd)
{
	if (dup2(data->fd1, STDIN_FILENO) < 0)
		exit_perror("dup2");
	if (dup2(fd[0][1], STDOUT_FILENO) < 0)
		exit_perror("dup2");
}

void last_cmd(t_data *data, int **fd, int i)
{
	if (dup2(fd[i - 1][0], STDIN_FILENO) < 0)
		exit_perror("dup2");
	if (dup2(data->fd2, STDOUT_FILENO) < 0)
		exit_perror("dup2");
}

void inter_cmd(int **fd, int i)
{
	if (dup2(fd[i - 1][0], STDIN_FILENO) < 0)
		exit_perror("dup2");
	if (dup2(fd[i][1], STDOUT_FILENO) < 0)
		exit_perror("dup2");
}

void create_child(int pid, int **fd, t_data *data, char **envp)
{
	int	i;

	i = -1;
		while (++i < data->nb_of_process)
		{
			pid = fork();
			if (pid == 0)
			{
				if (i == 0)
					first_cmd(data, fd);
				else if (!data->cmd_list->next)
					last_cmd(data, fd, i);
				else
					inter_cmd(fd, i);
				close_all_fd(data, fd);
				if (execve(data->cmd_list->path, data->cmd_list->param, envp) == -1)
					exit_perror("execve pid");
			}
			else if (pid == -1)
			{
				perror("fork");
				exit(2);
			}
			data->cmd_list = data->cmd_list->next;
	}
}

int	**malloc_pipes(int ac, t_data *data)
{
	int	**fd;
	int	i;

	i = 0;
	data->nb_of_process = ac - 3;
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

void set_pipe(t_data *data, int **fd)
{
	int i;

	i = 0;
	while (i < data->nb_of_process)
	{
		if (pipe(fd[i]) == -1)
			exit_perror("pipe");
		i++;
	}
}

int main(int argc, char **argv, char **envp)
 {
	int **fd;
	int pid;
	char **path_tab;
	t_data data;

	pid = 0;
	if (argc == 5)
	{
		init_data(&data);
		openfiles(argv, argc, &data);
		path_tab = split_env_path(envp);
		get_cmd(argc, argv, &data.cmd_list);
		get_cmd_path(&data.cmd_list, path_tab);
		fd = malloc_pipes(argc, &data);
		set_pipe(&data, fd);
		create_child(pid, fd, &data, envp);
		close_all_fd(&data, fd);
		if (waitpid(pid, NULL, 0) == -1)
			exit_perror("waitpid");
		free_cmd_list(&data.cmd_list);
		exit(0);
	}
	 exit(-1);
}
