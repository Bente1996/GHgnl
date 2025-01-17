/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:14:02 by bde-koni          #+#    #+#             */
/*   Updated: 2025/01/17 14:52:33 by bde-koni         ###   ########.fr       */
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
	

	if (fd < 0 || fd > OPEN_MAX || read(fd, 0, 0) == -1 || BUFFER_SIZE < 1) //met buffer 0 kom je nooit door bestand
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
		if (storage[j] == '\n')
			break; // eerste stukje van buffer gereturned, tot dat punt zijn nu \0's
		i++;
		j++;
	}
	storage[j + 1] = '\0'; // terminate storage
	return (storage); // hele of stukje buffer wordt opgestuurd
}

char	*make_line(int fd, char *buffer) // returns hele line
{
	char	*storage;
	char	*line; //groeit

	line = NULL;
	while (read(fd, buffer, BUFFER_SIZE) > 0) // zolang er wat te lezen valt
	{
		storage = buff_to_storage(buffer); // we krijgen wat storage binnen
		if (storage == NULL)
			return (NULL);
		line = storage_to_line(storage, line); //plak steeds een stukje storage aan groeiende line
		if (line == NULL)
			return (NULL);
		if (nl_check(line) == 1) // return wanneer \n gevonden is
			break;
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
	printf("line tot nu toe == %s\n", line);
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
	for (size_t i = 0; i < 5; i++)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
