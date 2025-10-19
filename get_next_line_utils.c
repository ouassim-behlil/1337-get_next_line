#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	len = ft_strlen(str);
	i = 0;
	ptr = malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

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
