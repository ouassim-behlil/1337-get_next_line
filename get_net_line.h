#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <libft.h>
#include <fcntl.h>

char	*ft_strdup(const char *str1);
char	*ft_strjoin(const char *str1, const char *str2);
int	get_next_line(const int fd, char **line);

#endif