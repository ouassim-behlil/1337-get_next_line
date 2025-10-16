#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	char			*p;

	uc = (unsigned char)c;
	p = (char *)ptr;
	i = 0;
	while (i < n)
		p[i++] = uc;
	return (ptr);
}
