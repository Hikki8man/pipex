#include "../include/pipex.h"

void	openfiles(char **av, int ac, t_data *data)
{
	data->fd1 = open(av[1], O_RDWR, S_IRWXU, S_IRWXG);
	if (data->fd1 == -1)
		exit_perror("open");
	data->fd2 = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (data->fd2 == -1)
		exit_perror("open");
}

static void	add_slash_to_path(char **path_tab)
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
	int		i;
	char	**paths_tab;

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
	t_cmd	*cmd;
	int		i;

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

void	get_cmd_path(t_cmd **cmd_list, char **path_tab)
{
	t_cmd	*tmp;
	int		i;

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
