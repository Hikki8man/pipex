/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:26:32 by jchevet           #+#    #+#             */
/*   Updated: 2021/09/26 14:26:34 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_cmd	*cmd_lst_last(t_cmd *cmd_l)
{
	while (cmd_l && cmd_l->next)
		cmd_l = cmd_l->next;
	return (cmd_l);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

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

void	free_cmd_list(t_cmd **cmd)
{
	t_cmd	*tmp;

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
