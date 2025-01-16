/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:04:17 by bde-koni          #+#    #+#             */
/*   Updated: 2025/01/08 17:28:47 by bde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;

	line = line_alloc(1);
	if (line == NULL)
		return (NULL);
	if (buffer != NULL)
	{
		line = buff_to_line(buffer, line);
		if (line == NULL)
			return (NULL);
	}
	line = update_line(buffer, line, fd);
	if (line == NULL)
		return (NULL);
	move_buff(buffer);
	return (line);
}

char	*line_alloc(size_t length)
{
	char	*line;
	size_t	i;

	i = 0;
	line = malloc(sizeof(char) * length);
	if (line == NULL)
		return (NULL);
	while (i < length)
	{
		line[i] = '\0';
		i++;
	}
	return (line);
}

int	main(void)
{
	int fd = open("fd.txt", O_RDONLY);
	char *line = get_next_line(fd);
	for (size_t i = 0; i < 5; i++)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
