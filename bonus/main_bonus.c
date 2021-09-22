#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		**fd;
	pid_t	pid;
	t_data	data;

	pid = 0;
	if (argc >= 5)
	{
		init_data(&data);
		data.path_tab = split_env_path(envp);
		get_cmd(argc, argv, &data.cmd_list);
		savefilenames(argv, argc, &data);
		fd = malloc_pipes(argc, &data);
		set_pipe(&data, fd);
		create_child(pid, fd, &data, envp);
		wait(NULL);
		close_all_fd(&data, fd);
		free_cmd_list(&data.cmd_list);
		return (0);
	}
	ft_putstr_nl_fd("Error\nArgument count < 5", 2);
	return (-1);
}
