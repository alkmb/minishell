/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:04:51 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/17 11:26:05 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_file_gnl(int fd, char *buffer)
{
	char	*new_buffer;
	int		error_hand;

	error_hand = 1;
	new_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new_buffer)
		return (free_buffer(&buffer));
	new_buffer[0] = '\0';
	while (error_hand > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		error_hand = read(fd, new_buffer, BUFFER_SIZE);
		if (error_hand > 0)
		{
			new_buffer[error_hand] = '\0';
			buffer = ft_join_and_free_gnl(buffer, new_buffer);
		}
	}
	free(new_buffer);
	if (error_hand == -1)
		return (free_buffer(&buffer));
	return (buffer);
}

char	*get_line_from(char *buffer)
{
	char	*max_pos;
	char	*new_line;
	int		len;

	max_pos = ft_strchr_gnl(buffer, '\n');
	len = (max_pos - buffer) + 1;
	new_line = ft_substr_gnl(buffer, 0, len);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*rest_buffer_gnl(char *buffer)
{
	char	*max_pos;
	char	*new_buffer;
	int		len;

	max_pos = ft_strchr_gnl(buffer, '\n');
	if (!max_pos)
	{
		new_buffer = NULL;
		return (free_buffer(&buffer));
	}
	len = (max_pos - buffer) + 1;
	if (!buffer[len])
		return (free_buffer(&buffer));
	new_buffer = ft_substr_gnl(buffer, len, ft_strlen_protect(buffer) - len + 1);
	free_buffer(&buffer);
	if (!new_buffer)
		return (NULL);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd] || (buffer[fd] && !ft_strchr_gnl(buffer[fd], '\n')))
		buffer[fd] = read_file_gnl(fd, buffer[fd]);
	line = get_line_from(buffer[fd]);
	if (!line)
		return (free_buffer(&buffer[fd]));
	buffer[fd] = rest_buffer_gnl(buffer[fd]);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	char *line1;
	char *line2;
	int fd1, fd2;
	
	fd1 = open("archivo1.txt", O_RDONLY);
	fd2 = open("archivo2.txt", O_RDONLY);
	line1= malloc(sizeof(char *));
	line2 = malloc(sizeof(char *));
	while (line1 || line2)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		printf("%s\n", line1);
		printf("%s\n", line2);
		free(line1);
		free(line2);

	}
	return (0);
}*/
