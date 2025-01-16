/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:04:17 by bde-koni          #+#    #+#             */
/*   Updated: 2025/01/08 17:31:22 by bde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*update_line(char	*buffer, char	*line, int fd)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (delim_len(line, '\n') == 0 && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		line = buff_to_line(buffer, line);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

char	*buff_to_line(char	*buffer, char	*line)
{
	char	*new_line;
	size_t	line_len;
	size_t	buff_add;

	line_len = delim_len(line, '\0');
	buff_add = delim_len(buffer, '\n');
	if (buff_add == 0)
		buff_add = delim_len(buffer, '\0');
	new_line = line_alloc(line_len + buff_add + 1);
	if (new_line == NULL)
		return (NULL);
	buff_line_join(new_line, line, buffer, buff_add);
	free(line);
	return (new_line);
}

void	buff_line_join(char *new_line, char *line, char *buffer, \
size_t buff_add)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		new_line[i] = line[i];
		i++;
	}
	while (j < buff_add)
	{
		new_line[i + j] = buffer[j];
		j++;
	}
}

void	move_buff(char *buffer)
{
	size_t	buff_len;
	size_t	line_len;
	size_t	i;

	buff_len = delim_len(buffer, '\0');
	line_len = delim_len(buffer, '\n');
	i = 0;
	if (buffer[line_len] == '\0')
	{
		while (i < BUFFER_SIZE)
		{
			buffer[i] = '\0';
			i++;
		}
		return ;
	}
	while (i <= buff_len - line_len)
	{
		buffer[i] = buffer[line_len + i];
		i++;
	}
	buffer[i] = '\0';
}

size_t	delim_len(char	*buffer, char delim)
{
	size_t	i;

	i = 0;
	if (delim != '\0')
	{
		while (buffer[i] != '\0')
		{
			if (buffer[i] == delim)
				return (i + 1);
			i++;
		}
		return (0);
	}
	while (buffer[i])
		i++;
	return (i);
}
