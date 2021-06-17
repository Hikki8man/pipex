//
// Created by Johan Chevet on 6/15/21.
//

#include "include/libft.h"

void	ft_free_str_tab(char **t)
{
	int	i;

	i = 0;
	if (t)
	{
		while (t[i])
		{
			free(t[i]);
			i++;
		}
		free(t);
	}
}
