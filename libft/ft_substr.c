#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	j;
	size_t			slength;

	i = 0;
	j = start;
	slength = ft_strlen(s);
	if (start >= slength)
		return (ft_strdup(""));
	sub = malloc(len + 1);
	if (sub == NULL)
		return (NULL);
	while (i < len && start + i < slength)
		sub[i++] = s[j++];
	sub[i] = '\0';
	return (sub);
}
