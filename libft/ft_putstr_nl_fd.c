#include "include/libft.h"

void	ft_putstr_nl_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
