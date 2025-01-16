/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:14:02 by bde-koni          #+#    #+#             */
/*   Updated: 2025/01/16 11:43:28 by bde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "limits.h"

	check buffer: alles of , tot \n naar line en return. wanneer \n gevonden null terminate wat gereturned is
	als buffer == \0, read

\0 storage?
read in buffer, buffer zit vol

zolang bytes_read <= BUFFER_SIZE
wel \n? tot hier willen we in de storage, dit kunnen we returnen
\0 buffer tot dit punt, zodat we er dalijk overheen lezen. index 0 = \0
geen \n? stop alles in storage en read nog een keer (loop)

read return 0, conditie voor lijn returnen

andere functie: check gereturnde lijn op \n
wel? return
niet? bewaar en wacht op meer

		if (buffer[i] == '\0' bytes_read < 0) //
			read();


char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char	*storage;
	size_t	storage_len;

	storage = malloc;
	if (fd < 0 || fd > OPEN_MAX || read(fd, 0, 0) == -1 || BUFFER_SIZE < 1) //met buffer 0 kom je nooit door bestand
		return (NULL);
	
	return (make_line(fd, buffer));
}


char	*buff_to_storage(int fd, char *buffer)
{
	char	*storage;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	storage = malloc;
	while (i < BUFFER_SIZE && buffer[i] == '\0') // skip wat we al opgestuurd hebben, edge case: buffer is precies line
		i++;
	while (i < BUFFER_SIZE) //zolang we niet aan het einde van de buffer zijn
	{
		storage[j] = buffer[i];
		buffer[i] = '\0';
		if (storage[j] == '\n')
			return (storage); // eerste stukje van buffer gereturned, tot dat punt zijn nu \0's
		i++;
		j++;
	}
	return (storage); //hele buffer wordt opgestuurd
}

char	*make_line(int fd, char *buffer) // returns hele line
{
	char	*storage;
	char	*line;
	size_t	i;
	size_t	j;
	
	i = 0;
	j = 0;
	
	while (read(fd, buffer, BUFFER_SIZE) > 0) // zolang er wat te lezen valt
	{
		buff_to_storage(fd, buffer); // we krijgen wat storage binnen
		line = malloc;
		while (i < strlen(storage)) // plak stukje aan lijn
		{
			line[j] = storage[i];
			i++;
			j++;
		}
		if (strlen(storage) != BUFFER_SIZE) // kregen we maar een stukje? stuur op
		{
			free(storage);
			return (line);
		}
		i = 0;
	}
}

size_t	strlen(char *storage)
{
	return (storage_len);
}
