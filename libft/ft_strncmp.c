#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == num)
		return (0);
	return ((int)((unsigned char )str1[i] - (unsigned char)str2[i]));
}
