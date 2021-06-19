//
// Created by Johan Chevet on 6/19/21.
//

#include "include/libft.h"

void	ft_free_int_tab(int **t)
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
