#include <stdio.h>
#include <unistd.h>
#include "libft/include/libft.h"
#include <fcntl.h>
#include <errno.h>
#define TRUE 1
#define FALSE 0

//fd[0] = READ
//fd[1] = WRITE

typedef struct s_cmd
{
	char	*name;
	char	*path;
	char	**param;
	int 	nb_param;
	struct s_cmd *next;
}t_cmd;

t_cmd	*cmd_lst_last(t_cmd *cmd_l)
{
	while (cmd_l && cmd_l->next)
		cmd_l = cmd_l->next;
	return (cmd_l);
}


t_cmd *new_cmd(void)
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->param = NULL;
	cmd->name = 0;
	cmd->path = NULL;
	cmd->nb_param = 0;
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

void exit_perror(char *name)
{
	perror(name);
	exit(EXIT_FAILURE);
}

void	add_slash_to_path(char **path_tab)
{
	char	*tmp;
	int		i;

	i = 0;
	while (path_tab[i])
	{
		tmp = ft_strjoin(path_tab[i], "/");
		if (!tmp)
			exit(-1);
		free(path_tab[i]);
		path_tab[i] = tmp;
		i++;
	}
}


char	**split_env_path(char **envp)
{
	int	i;
	char **paths_tab;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	envp[i] += 5;
	paths_tab = ft_split(envp[i], ':');
	add_slash_to_path(paths_tab);
	return (paths_tab);
}

void find_cmd_path(char **paths_tab, t_cmd *cmd_list, char **argv)
{

}

int 	nb_of_param(char **param)
{
	int	i;


	i = 0;
	while (param[i])
		i++;
	return (i);
}

void	get_cmd(int ac, char **av, t_cmd **cmd_l)
{
	t_cmd *cmd;
	int i;

	i = 2;
	while (i < ac - 1)
	{
		cmd = new_cmd();
		if (!cmd)
			exit_perror("new_cmd");
		cmd->param = ft_split(av[i], ' ');
		cmd->name = *cmd->param;
		cmd->nb_param = nb_of_param(cmd->param);
		add_back(cmd_l, cmd);
		i++;
	}
}


void get_cmd_path(t_cmd **cmd_list, char **path_tab)
{
	t_cmd	*tmp;
	int 	i;

	tmp = *cmd_list;
	while (tmp)
	{
		i = 0;
		while (path_tab[i])
		{
			tmp->path = ft_strjoin(path_tab[i], tmp->name);
			if (tmp->path == NULL)
				exit(2);
			if (open(tmp->path, O_RDONLY) != -1)
				break ;
			free(tmp->path);
			tmp->path = NULL;
			i++;
		}
		if (tmp->path == NULL)
			exit(3); //cmd not found / valid
		tmp = tmp->next;
	}
	ft_free_str_tab(path_tab);
}

int main(int argc, char **argv, char **envp)
 {
	int pid1;
	int pid2;
	int fd[2];
	char *line;
	char **path_tab;
	t_cmd *cmd_list;

	cmd_list = NULL;
	char *arr[] = {
			 "ls",
			 "-la",
			 NULL
	};
	path_tab = split_env_path(envp);
	get_cmd(argc, argv, &cmd_list);
	get_cmd_path(&cmd_list, path_tab);
	int i;

	while (cmd_list)
	{
		i = 0;
		printf("Name: %s\nNB OF PARAM: %d\n", cmd_list->name,
		 cmd_list->nb_param);
		while (cmd_list->param[i])
		{
			printf("param %d: %s\n", i + 1, cmd_list->param[i]);
			i++;
		}
		cmd_list = cmd_list->next;
	}
//	while (paths_tab[i])
//	{
//		printf("%s\n", paths_tab[i]);
//		i++;
//	}
	 int std_out = dup(STDIN_FILENO);
//	if (pipe(fd) == -1)
//		exit_perror("pipe");
//	pid1 = fork();
//	if (pid1 == -1)
//		exit_perror("fork");
//	if (pid1 == 0) {
//
//		dup2(fd[1], STDOUT_FILENO);
//		close(fd[0]);
//		close(fd[1]);
//		execve("ls", arr, envp);
//	}
//	 pid2 = fork();
//	 if (pid2 == -1)
//		 exit_perror("fork");
//	 if (pid2 == 0)
//	 {
//	 	waitpid(pid1, NULL, 0);
//	 	dup2(fd[0], STDIN_FILENO);
//	 	close(fd[0]);
//	 	close(fd[1]);
//		 int ret = execlp(
//				 "/usr/bin/grep",
//				 "grep",
//				 "libft",
//				 NULL
//		 );
//		 if (ret == -1) {
//			 perror("execlp");
//			 exit(EXIT_FAILURE);
//		 }
//
//	 }
//	close(fd[1]);
//	close(fd[0]);
//	waitpid(pid1, NULL, 0);
//	waitpid(pid2, NULL, 0);
	return 0;
}
