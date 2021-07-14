#include "../include/pipex.h"

//fd[0] = READ
//fd[1] = WRITE
//TODO error compile libft, check fsanitize, check how waitpid work (waitall process to finish before exit)
int	main(int argc, char **argv, char **envp)
{
	int		**fd;
	pid_t	pid;
	char	**path_tab;
	t_data	data;

	pid = 0;
//	if (argc == 5)
//	{
		init_data(&data);
		path_tab = split_env_path(envp);
		get_cmd(argc, argv, &data.cmd_list);
		get_cmd_path(&data.cmd_list, path_tab);
		fd = malloc_pipes(argc, &data);
		openfiles(argv, argc, &data);
		set_pipe(&data, fd);
		printf("main pro %d\n", getpid());
		create_child(pid, fd, &data, envp);
		printf("pas finito\n");
//		waitpid(pid, NULL, 0);
		printf("finito\n");
		close_all_fd(&data, fd);
		free_cmd_list(&data.cmd_list);
		return (0);
//	}
	ft_putstr_nl_fd("Error\nArgument count != 5\n", 2);
	return (-1);
}
