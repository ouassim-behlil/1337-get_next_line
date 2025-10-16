#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dsize)
{
	size_t	i;
	size_t	slength;

	slength = ft_strlen(src);
	if (dsize == 0)
		return (slength);
	i = 0;
	while (i < dsize - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (slength);
}
