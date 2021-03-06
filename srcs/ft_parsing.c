/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:01:40 by jchevet           #+#    #+#             */
/*   Updated: 2021/09/26 14:02:06 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	savefilenames(char **av, int ac, t_data *data)
{
	data->filename1 = av[1];
	data->filename2 = av[ac - 1];
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
		{
			ft_free_str_tab(path_tab);
			exit(EXIT_FAILURE);
		}
		free(path_tab[i]);
		path_tab[i] = tmp;
		i++;
	}
}

char	**split_env_path(char **envp)
{
	int		i;
	int		found_path;
	char	**paths_tab;

	i = -1;
	found_path = 0;
	paths_tab = NULL;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			found_path = 1;
			break ;
		}
	}
	if (found_path == 0)
		return (paths_tab);
	envp[i] += 5;
	paths_tab = ft_split(envp[i], ':');
	if (paths_tab == NULL)
		exit(EXIT_FAILURE);
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
		cmd = NULL;
		cmd = new_cmd();
		if (!cmd)
		{
			ft_putstr_fd("Error\nmalloc failed\n", 2);
			exit_failure(cmd_l);
		}
		cmd->param = ft_split(av[i], ' ');
		if (!cmd->param)
		{
			ft_free_tab(cmd->param, i);
			exit_perror("new_cmd");
		}
		cmd->name = *cmd->param;
		add_back(cmd_l, cmd);
		i++;
	}
}

void	get_cmd_path(t_cmd *cmd_list, t_data *data)
{
	int		i;
	char	*path;

	i = -1;
	if (data->path_tab)
	{
		while (data->path_tab[++i])
		{
			path = ft_strjoin(data->path_tab[i], cmd_list->name);
			if (path == NULL)
				exit_failure(&data->cmd_list);
			if (path_exist(path, cmd_list) == 1)
			{
				free(path);
				break ;
			}
			free(path);
			path = NULL;
		}
	}
	ft_free_str_tab(data->path_tab);
	if (command_not_found(cmd_list->path, cmd_list->name))
		exit_failure(&data->cmd_list);
}
