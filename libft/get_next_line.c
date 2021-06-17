/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 13:23:02 by jchevet           #+#    #+#             */
/*   Updated: 2020/12/05 12:59:17 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

static int	ft_str_treatment(char **str, int fd, char **line, char *tmp)
{
	int	i;

	i = 0;
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
		i++;
	if (str[fd][i] == '\n')
	{
		*line = ft_substr(str[fd], 0, i);
		tmp = str[fd];
		str[fd] = ft_substr(str[fd], i + 1, ft_strlen(str[fd]));
		free(tmp);
		return (1);
	}
	else
	{
		*line = ft_strdup(str[fd]);
		free(str[fd]);
		str[fd] = NULL;
		return (0);
	}
}

static int	check_errors(int fd, char **line, char **str)
{
	if (read(fd, str[fd], 0) != 0 || line == NULL || BUFFER_SIZE == 0)
		return (0);
	return (1);
}

static void	ft_strjoiner(char **str, t_var *var)
{
	var->tmp = *str;
	*str = ft_strjoin(*str, var->buffer);
	free(var->tmp);
}

int	get_next_line(int fd, char **line)
{
	static char	*str[10240];
	t_var		var;

	if (!check_errors(fd, line, str))
		return (-1);
	while (1)
	{
		var.bytes_read = read(fd, var.buffer, BUFFER_SIZE);
		if (var.bytes_read == 0)
			break ;
		var.buffer[var.bytes_read] = '\0';
		if (!str[fd])
			str[fd] = ft_strdup(var.buffer);
		else
			ft_strjoiner(&str[fd], &var);
		if (str[fd] == NULL)
			return (-1);
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	if (str[fd] != NULL)
		return (ft_str_treatment(str, fd, line, var.tmp));
	*line = ft_strdup("");
	return (0);
}
