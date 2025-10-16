#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	size_t				i;
	const unsigned char	*p1;
	const unsigned char	*p2;

	i = 0;
	p1 = (const unsigned char *)ptr1;
	p2 = (const unsigned char *)ptr2;
	while (i < num && p1[i] == p2[i])
		i++;
	if (i == num)
		return (0);
	return ((int)(p1[i] - p2[i]));
}
