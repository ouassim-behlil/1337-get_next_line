/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouassim <ouassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:22:47 by obehlil           #+#    #+#             */
/*   Updated: 2025/10/19 21:09:26 by ouassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	has_complete_line(char **leftover, char **line)
{
	char		*temp_leftover;
	char		*new_leftover;
	int			i;

	i = 0;
	temp_leftover = *leftover;
	if (!temp_leftover)
		return (0);
	while (temp_leftover[i] && temp_leftover[i] != '\n')
		i++;
	if (temp_leftover[i] != '\n')
		return (0);
	*line = ft_substr(temp_leftover, 0, i + 1);
	if (!(*line))
		return (-1);
	new_leftover = ft_strdup(temp_leftover + i + 1);
	if (!(new_leftover))
		return (-1);
	free(*leftover);
	*leftover = new_leftover;
	return (1);
}

static int	read_buffers(const int fd, char **leftover, char **line)
{
	char	*buffer;
	char	*temp;
	int		status;

	if (!*leftover)
		*leftover = ft_strdup("");
	buffer = malloc(BUFFER_SIZE + 1);
	if (!(buffer))
		return (0);
	status = read(fd, buffer, BUFFER_SIZE);
	if (status <= 0)
	{
		if (status == -1 || !*leftover || !ft_strlen(*leftover))
			return (free(buffer), 0);
		*line = ft_strdup(*leftover);
		return (free(*leftover), *leftover = NULL, free(buffer), 1);
	}
	buffer[status] = '\0';
	temp = ft_strjoin(*leftover, buffer);
	if (!temp)
		return (free(buffer), 0);
	free(*leftover);
	*leftover = temp;
	return (free(buffer), 1);
}

char	*get_next_line(const int fd)
{
	static char		*leftover[1024];
	char			*line;
	int				status;

	line = NULL;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	if (leftover[fd])
	{
		status = has_complete_line(&leftover[fd], &line);
		if (status == 1)
			return (line);
		else if (status == -1)
			return (NULL);
	}
	while (read_buffers(fd, &leftover[fd], &line) == 1)
	{
		if (line && !leftover[fd])
			return (line);
		status = has_complete_line(&leftover[fd], &line);
		if (status == 1)
			return (line);
	}
	return (NULL);
}
