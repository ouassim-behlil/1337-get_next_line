#include "libft.h"

int	ft_tolower(int c)
{
	if (c == EOF)
		return (EOF);
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
