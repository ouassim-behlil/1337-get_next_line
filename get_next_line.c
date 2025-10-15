/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obehlil <obehlil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:22:47 by obehlil           #+#    #+#             */
/*   Updated: 2025/10/15 17:57:32 by obehlil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char	*leftover[1024];
	char			*chunk;


	// handle special Cases when we need to return -1
	if (!line || (fd < 0 || fd > 1024) || (read(fd, leftover[fd], 0) == -1) \
		!(chunk = malloc(BUFFER_SIZE + 1)))
		return (-1);

	// check if the leftover contains a complete line and return 1
	if (leftover[fd])
	{
		if (has_complete_line(&leftover[fd], line))
			return (1);
	}
	// read BUFFER_SIZE chunks untill a complete line occured
	if (read_chunks(fd, &chunk, &leftover[fd], line) != 1)
		return (-1)
}

static int	has_complete_line(char **leftover, char **line)
{
	char		*temp_leftover;
	char		*new_leftover;
	int		i;

	i = 0;
	temp_leftover = *leftover;
	if (!temp_leftover)
		return (0);
	while (temp_leftover[i] != '\n')
	{
		if(!temp_leftover[i++])
			return (0);
	}
	if (!(*line = ft_substr((const char *)temp_leftover, 0, i)))
		return (-1);
	if (!(new_leftover = ft_strdup(temp_leftover+ i + 1)))
		return (-1);
	free(*leftover);
	*leftover = new_leftover;
	return (1);
}

static int	read_chunks(const int fd, char **chunk, )