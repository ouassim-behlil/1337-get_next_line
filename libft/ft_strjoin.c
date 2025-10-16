#include "libft.h"

char	*ft_strjoin(const char *prefix, const char *suffix)
{
	size_t			plength;
	size_t			slength;
	size_t			i;
	size_t			j;
	char			*join;

	plength = ft_strlen(prefix);
	slength = ft_strlen(suffix);
	i = 0;
	j = 0;
	join = malloc(plength + slength + 1);
	if (join == NULL)
		return (NULL);
	while (i < plength)
		join[j++] = prefix[i++];
	i = 0;
	while (i < slength)
		join[j++] = suffix[i++];
	join[j] = '\0';
	return (join);
}
