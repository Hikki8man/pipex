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

//--Command list----------------------------------------------------------------
t_cmd	*new_cmd(void);
void	add_back(t_cmd **cmd_list, t_cmd *new_cmd);
t_cmd	*cmd_lst_last(t_cmd *cmd_l);
void	free_cmd_list(t_cmd **cmd);

//--Init------------------------------------------------------------------------
void	init_data(t_data *data);
void	set_pipe(t_data *data, int **fd);

//--Parsing---------------------------------------------------------------------
void	get_cmd_path(t_cmd **cmd_list, char **path_tab);
void	get_cmd(int ac, char **av, t_cmd **cmd_l);
char	**split_env_path(char **envp);
void	openfiles(char **av, int ac, t_data *data);
int		path_exist(char *path);

//--Malloc pipe-----------------------------------------------------------------
int		**malloc_pipes(int ac, t_data *data);

//--Create process--------------------------------------------------------------
void	create_child(int pid, int **fd, t_data *data, char **envp);

//--Close fd--------------------------------------------------------------------
void	close_all_fd(t_data *data, int **fd);
void	close_perror(int fd, char *name);

//--Exit / Errors---------------------------------------------------------------
int		command_not_found(char *path, char *name);
void	exit_perror(char *name);
void 	exit_failure(t_cmd **cmd, char **path_tab);

#endif
