#include "libft.h"

static int	is_in_set(int c, const char *set)
{
	size_t		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s, const char *set)
{
	size_t		start;
	size_t		end;
	size_t		len;

	start = 0;
	len = ft_strlen(s);
	if (len == 0)
		return (ft_strdup(""));
	end = len - 1;
	while (s[start] && is_in_set(s[start], set))
		start++;
	while (end >= start && is_in_set(s[end], set))
		end--;
	return (ft_substr(s, (unsigned int)start, (end - start + 1)));
}
