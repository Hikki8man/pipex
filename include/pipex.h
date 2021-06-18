//
// Created by Johan Chevet on 6/18/21.
//

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_cmd
{
	char	*name;
	char	*path;
	char	**param;
	struct	s_cmd *next;
}t_cmd;

typedef struct s_data
{
	int		fd1;
	int		fd2;
	int 	nb_of_process;
	t_cmd	*cmd_list;
}t_data;


#endif
