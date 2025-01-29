/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:14:02 by bde-koni          #+#    #+#             */
/*   Updated: 2025/01/29 13:03:13 by bde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	ssize_t		bytes_read;

	bytes_read = 1;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE < 1)
		return (NULL);
	return (make_line(fd, buffer, bytes_read));
}

char	*make_line(int fd, char *buffer, ssize_t bytes_read)
{
	char	*storage;
	char	*line;

	line = NULL;
	bytes_read = read_if_buff_empty(fd, buffer, bytes_read);
	if (bytes_read == -1)
		return (NULL);
	while (bytes_read > 0)
	{
		storage = buff_to_storage(buffer);
		if (storage == NULL)
			return (free(line), NULL);
		line = storage_to_line(storage, line);
		if (line == NULL)
			return (NULL);
		if (nl_check(line) == true)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}

char	*buff_to_storage(char *buffer)
{
	char	*storage;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	storage = malloc(BUFFER_SIZE + 1);
	if (storage == NULL)
		return (NULL);
	while (i < BUFFER_SIZE && buffer[i] == '\0')
		i++;
	while (i < BUFFER_SIZE)
	{
		storage[j] = buffer[i];
		buffer[i] = '\0';
		i++;
		j++;
		if (storage[j - 1] == '\n')
			break ;
	}
	storage[j] = '\0';
	return (storage);
}

char	*storage_to_line(char *storage, char *old_line)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	line = line_alloc(storage, old_line);
	if (line == NULL)
		return (NULL);
	while (old_line != NULL && old_line[i] != '\0')
	{
		line[i] = old_line[i];
		i++;
	}
	free(old_line);
	while (storage[j] != '\0')
	{
		line[i + j] = storage[j];
		j++;
	}
	line[i + j] = '\0';
	free(storage);
	return (line);
}
