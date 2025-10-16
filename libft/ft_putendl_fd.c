#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	unsigned int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		ft_putchar_fd(s[i++], fd);
	ft_putchar_fd('\n', fd);
}
