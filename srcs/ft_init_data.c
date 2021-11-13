/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:28:13 by jchevet           #+#    #+#             */
/*   Updated: 2021/09/26 14:28:14 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_data(t_data *data)
{
	data->fd1 = 0;
	data->fd2 = 0;
	data->cmd_list = NULL;
	data->nb_of_process = 0;
}
