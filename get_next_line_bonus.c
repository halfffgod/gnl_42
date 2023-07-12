/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbadalia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 15:51:25 by nbadalia          #+#    #+#             */
/*   Updated: 2023/04/18 11:15:25 by nbadalia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*rem[MAX_FD];
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(rem);
		free(buffer);
		rem[fd] = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_buffer(fd, rem[fd], buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	rem[fd] = set_line(line);
	return (line);
}

char	*set_line(char *line_buffer)
{
	char	*rem;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	rem = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*rem == 0)
	{
		free(rem);
		rem = NULL;
	}
	line_buffer[i + 1] = 0;
	return (rem);
}

char	*fill_buffer(int fd, char *rem, char *buffer)
{
	ssize_t	read_buf;
	char	*tmp;

	read_buf = 1;
	while (read > 0)
	{
		read_buf = read(fd, buffer, BUFFER_SIZE);
		if (read_buf == -1)
		{
			free(rem);
			return (NULL);
		}
		else if (read_buf == 0)
			break ;
		buffer[read_buf] = 0;
		if (!rem)
			rem = ft_strdup("");
		tmp = rem;
		rem = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (rem);
}
