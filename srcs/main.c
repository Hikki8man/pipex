#include "../include/pipex.h"

//fd[0] = READ
//fd[1] = WRITE

int	main(int argc, char **argv, char **envp)
{
	int		**fd;
	int		pid;
	char	**path_tab;
	t_data	data;

	pid = 0;
//	if (argc == 5)
//	{
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
		return (0);
//	}
	ft_putstr_nl_fd("Error\nArgument count != 5\n", 2);
	return (-1);
}
