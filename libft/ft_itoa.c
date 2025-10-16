#include "libft.h"

static size_t	count_int_chars(int n)
{
	size_t			count;
	unsigned int	num;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		num = (unsigned int)(-n);
	}
	else
		num = n;
	while (num != 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

static void	ft_fill(char *anum, int n, size_t size)
{
	unsigned int		num;
	int					i;

	i = (int)size - 1;
	if (n < 0)
	{
		anum[0] = '-';
		num = (unsigned int)(-n);
	}
	else
		num = n;
	while (num > 0)
	{
		anum[i--] = (num % 10) + '0';
		num /= 10;
	}
	anum[size] = '\0';
}

char	*ft_itoa(int n)
{
	size_t			size;
	char			*anum;

	size = count_int_chars(n);
	anum = malloc(size + 1);
	if (!anum)
		return (NULL);
	if (n == 0)
	{
		anum[0] = '0';
		anum[1] = '\0';
	}
	else
		ft_fill(anum, n, size);
	return (anum);
}
