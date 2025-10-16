#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	size_t				len;
	char				*smapped;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	smapped = malloc(len + 1);
	if (!smapped)
		return (NULL);
	while (i < len)
	{
		smapped[i] = f(i, s[i]);
		i++;
	}
	smapped[i] = '\0';
	return (smapped);
}
