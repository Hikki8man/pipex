/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:27:56 by jchevet           #+#    #+#             */
/*   Updated: 2021/09/26 14:27:58 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	command_not_found(char *path, char *name)
{
	if (path == NULL)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (1);
	}
	return (0);
}

int	path_exist(char *path, t_cmd *cmd)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		if (cmd->path != NULL)
			free(cmd->path);
		cmd->path = ft_strdup(path);
		if (access(path, X_OK) == 0)
		{
			close_perror(fd, "open");
			return (1);
		}
		else
		{
			close_perror(fd, "open");
			return (0);
		}
	}
	return (0);
}

void	exit_perror(char *name)
{
	perror(name);
	exit (EXIT_FAILURE);
}

void	exit_failure(t_cmd **cmd, char **path_tab)
{
	ft_free_str_tab(path_tab);
	free_cmd_list(cmd);
	exit(EXIT_FAILURE);
}
