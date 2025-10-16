#include "libft.h"

int	ft_toupper(int c)
{
	if (c == EOF)
		return (EOF);
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
