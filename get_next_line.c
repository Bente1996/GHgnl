/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:14:02 by bde-koni          #+#    #+#             */
/*   Updated: 2025/01/21 17:18:05 by bde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "limits.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	
	if (fd < 0 || fd > OPEN_MAX  || BUFFER_SIZE < 1) //met buffer 0 kom je nooit door bestand
		return (NULL);
	return (make_line(fd, buffer));
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
	while (i < BUFFER_SIZE && buffer[i] == '\0') // skip wat we al opgestuurd hebben, edge case: buffer is precies line
		i++;
	while (i < BUFFER_SIZE) //zolang we niet aan het einde van de buffer zijn
	{
		storage[j] = buffer[i];
		buffer[i] = '\0';
		i++;
		j++;
		if (storage[j - 1] == '\n')
			break; // eerste stukje van buffer gereturned, tot dat punt zijn nu \0's
	}
	storage[j] = '\0'; // terminate storage
	return (storage); // hele of stukje buffer wordt opgestuurd
}

ssize_t	ft_read(int fd, char *buffer, ssize_t bytes_read)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE && buffer[i] == '\0') // skip wat we al opgestuurd hebben, edge case: buffer is precies line
		i++;
	if (i == BUFFER_SIZE) // wanneer hele buffer gevuld is met \0s
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		// if (bytes_read == -1)
		// 	return (NULL);
	}
	return (bytes_read);
}

char	*make_line(int fd, char *buffer) // returns hele line
{
	char	*storage;
	char	*line; //groeit
	ssize_t	bytes_read;
	//size_t	i;

	line = NULL;
	bytes_read = 1;
	// i = 0;
	// while (i < BUFFER_SIZE && buffer[i] == '\0') // skip wat we al opgestuurd hebben, edge case: buffer is precies line
	// 	i++;
	// if (i == BUFFER_SIZE) // wanneer hele buffer gevuld is met \0s
	// {
	// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
	// 	if (bytes_read == -1)
	// 		return (NULL);
	// }
	bytes_read = ft_read(fd, buffer, bytes_read);
	if (bytes_read == -1)
		return (NULL);
	while (bytes_read > 0)
	{
		storage = buff_to_storage(buffer); // we krijgen wat storage binnen
		if (storage == NULL)
			return (NULL);
		line = storage_to_line(storage, line); //plak steeds een stukje storage aan groeiende line
		if (line == NULL)
			return (NULL);
		if (nl_check(line) == 1) // return wanneer \n gevonden is, in while loop verchil??
			break;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(line);
			return (NULL);
		}
	}
	return (line);
}

char	*storage_to_line(char *storage, char *old_line) // join en alloceer // old line freeen?
{
	char	*line;
	size_t	i;
	size_t	j;
	size_t	line_len;

	i = 0;
	j = 0;
	if (old_line == NULL)
		line_len = 0;
	else
		line_len = ft_strlen(old_line);
	line = malloc(line_len + ft_strlen(storage) + 1); // line neemt huidige lengte van line + storage + \0 aan
	if (line == NULL)
	{
		free(old_line);
		free(storage);
		return (NULL);
	}
	while (old_line != NULL && old_line[i] != '\0')
	{
		line[i] = old_line[i];
		i++;
	}
	free(old_line);
	while (storage[j] != '\0') // plak stukje storage aan lijn
	{
		line[i + j] = storage[j]; // voeg oude toe
		j++;
	}
	line[i + j] = '\0'; // terminate line
	free(storage); //weg halen wat we hebben toegevoegd
	return (line); // return geupdatete line
}

size_t	ft_strlen(char *str)
{
	size_t	length;
	
	length = 0;
	while (str[length] != '\0')
		length++;
	return (length);
}

int	nl_check(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	main()
{
	int fd = open("fd.txt", O_RDONLY);
	char *line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}

// int main()
// {
// 	char *line;
// 	int fd = open("fd.txt", O_RDONLY);

// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
	
// }