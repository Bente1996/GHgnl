/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:59:41 by bde-koni          #+#    #+#             */
/*   Updated: 2024/12/12 13:17:02 by bde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char	*get_next_line(int fd)
{	
	ssize_t	i;
	static char	*storage[i];

	i = 0;
	
	if (fd < 0 || i <= 0)
		return NULL;
	if (storage == NULL)
	{
		free(storage);
		return (NULL);
	}
	return extract_line(&storage[fd]);
}

static char	*read_and_add(int fd, char *storage) //read buffer and /0 it. join new with old content. return/save storage.
{
	char	buffer[50];
	ssize_t	bytes_read; // our index
	char	*joined;

	bytes_read = read(fd, buffer, sizeof(buffer) + 1); //read returns bytes read
	while (buffer[bytes_read] > 1) // as long as there is something in buffer keep adding to make a line :)
	{
		buffer[bytes_read] = '\0';
		joined = ft_strjoin(storage, buffer); //allocate new string CUSTOM STRJOIN TOT NEW LINE
		free(storage); // remove old line content from heap
		storage = joined; // line contains the new updated content (old + new readings)
		if (ft_strchr(buffer, '\n')) //check for \n, break if so otherwise continue with appending storage EARLIER
			break;
	}
	if (bytes_read < 0) // 0 read is EOF
	{
		return (NULL);
	}
	return (storage); // we return all that we've read so far! (not more than a line though)
}

static char	*make_line(char **storage) // check storage for \n or \0 (line). allocate memory for this line (incl \n). remove extracted line from storage. return line.
{
	char	*line;
	char	*temp;
	size_t	i;
	
	i = 0;
	if (*storage == NULL || **storage == NULL)
		return (NULL);
	if (storage[i] == '\0' && storage[i] != '\n')
	{
		i++; // look if we can make a line
	}
	storage[i] = '\n'; // not sure
	line = malloc(i + 1);
	if (line == NULL)
		return (NULL);
	
	return (line); // exactly one line
}

static char *extract_line(char **storage) {
    char *line;
    char *temp;
    size_t i = 0;

    if (!*storage || !**storage)
        return NULL;

    // Find the newline or end of string
    while ((*storage)[i] && (*storage)[i] != '\n')
        i++;

    // Allocate memory for the line (include \n if found)
    line = malloc(i + 1 + ((*storage)[i] == '\n')); // make sure to allocate the right amount
    if (!line)
        return NULL;
    ft_strncpy(line, *storage, i + ((*storage)[i] == '\n')); // dst src n
    line[i + ((*storage)[i] == '\n')] = '\0';

    // Update storage (remove the extracted line)
    temp = ft_strdup((*storage)[i] == '\n' ? *storage + i + 1 : NULL);
    free(*storage);
    *storage = temp;

    return line;
}
