#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*cs;

	i = 0;
	cs = (char *)s;
	while (i < n)
		cs[i++] = '\0';
}
