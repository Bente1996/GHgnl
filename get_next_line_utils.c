/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 17:01:12 by bde-koni          #+#    #+#             */
/*   Updated: 2025/01/28 20:59:55 by bde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*line_alloc(char *storage, char *old_line)
{
	char	*line;
	size_t	line_len;

	if (old_line == NULL)
		line_len = 0;
	else
		line_len = ft_strlen(old_line);
	line = malloc(line_len + ft_strlen(storage) + 1);
	if (line == NULL)
	{
		free(old_line);
		free(storage);
		return (NULL);
	}
	return (line);
}

ssize_t	read_if_buff_empty(int fd, char *buffer, ssize_t bytes_read)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE && buffer[i] == '\0')
		i++;
	if (i == BUFFER_SIZE)
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	return (bytes_read);
}

bool	nl_check(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (true);
		i++;
	}
	return (false);
}

size_t	ft_strlen(char *str)
{
	size_t	length;

	length = 0;
	while (str[length] != '\0')
		length++;
	return (length);
}
