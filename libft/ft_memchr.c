#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t				i;
	const unsigned char	*s;
	unsigned char		*m;

	i = 0;
	s = (const unsigned char *)str;
	m = (unsigned char *)str;
	while (i < n)
	{
		if (s[i] == (unsigned char)c)
			return (&m[i]);
		i++;
	}
	return (NULL);
}
