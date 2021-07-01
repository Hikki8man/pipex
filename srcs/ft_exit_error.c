//
// Created by Johan Chevet on 6/19/21.
//

#include "../include/pipex.h"

int	command_not_found(char *path, char *name)
{
	if (path == NULL)
	{
		ft_printf("%s: command not found\n", name);
		return (1);
	}
	return (0);
}

int	path_exist(char *path)
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

void	exit_perror(char *name)
{
	perror(name);
	exit (2);
}

void 	exit_failure(t_cmd **cmd, char **path_tab)
{
	ft_free_str_tab(path_tab);
	free_cmd_list(cmd);
	exit(EXIT_FAILURE);
}
