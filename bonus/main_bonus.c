/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:29:46 by jchevet           #+#    #+#             */
/*   Updated: 2021/09/26 14:29:48 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc >= 5)
	{
		init_data(&data);
		get_cmd(argc, argv, &data.cmd_list);
		savefilenames(argv, argc, &data);
		data.nb_of_process += argc - 3;
		create_child(&data, envp);
		free_cmd_list(&data.cmd_list);
		return (0);
	}
	ft_putstr_fd("Error\nArgument count < 5\n", 2);
	ft_putstr_fd("FILENAME | CMD | CMD | FILENAME\n", 2);
	return (-1);
}