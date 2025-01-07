/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:04:17 by bde-koni          #+#    #+#             */
/*   Updated: 2025/01/07 16:08:30 by bde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>

char	*get_next_line(int fd) //returns 1 line
{
	static char	buffer[BUFFER_SIZE + 1];
	char	*line;

	line = line_alloc(1); //allocate room for line at least 1 for /0, in buff_to_line we expand
	if (line == NULL) // weg??
		return (NULL);
	if (buffer != NULL) //if there is already something in the buffer from last call
	{
		line = buff_to_line(buffer, line); //add leftovers to new line, what if multiple lines? we dont call read again
		if (line == NULL)
			return (NULL);
	}
	line = update_line(buffer, line, fd); //only read more when leftovers are added, update line until \n found, so there cant be multiple lines? there can be
	if (line == NULL)
		return (NULL);
	move_buff(buffer); //remove until first \n shift the rest
	return (line); //return
}

char	*update_line(char	*buffer, char	*line, int fd)
{
	ssize_t	bytes_read;

	bytes_read = 1; //set to 1 to enter loop
	while (delim_len(line, '\n') == 0 && bytes_read > 0) //update line and read into buffer aslong as there is something in txt an no \n in line yet
	{
		bytes_read = read(fd, buffer, [BUFFER_SIZE + 1]); //fill up buffer
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0'; // \0 buffer
		line = buff_to_line(buffer, line); //Append buffer content to line
		if (line == NULL)
			return (NULL);
	}
	return (line); //return updated line, if no \0 present just return the line
}

char	*buff_to_line(char	*buffer, char	*line) // add new content to line 
{
	char	*new_line;
	size_t	line_len;
	size_t	buff_add;

	line_len = delim_len(line, '\0'); // length of line until \0 (current line)
	buff_add = delim_len(buffer, '\n'); // length of buff until \n
	if (buff_add = 0)
		buff_add = delim_len(buffer, '\0');
	new_line = line_alloc(line_len + buff_add + 1); //allocate room for new line
	if (new_line == NULL)
		return (NULL);
	buff_line_join(new_line, line, buffer, buff_add); //Copy all characters up to and including the \n (or until the buffer ends) to new line
	free(line); //free old line, new line basically becomes old line
	return (new_line); //return updated line
}

void	buff_line_join(char *new_line, char *line, char *buffer, size_t buff_add)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		new_line[i] = line[i]; //put old line in new line
		i++;
	}
	while (j < buff_add) //dont add more buffer than needed
	{
		new_line[i + j] = buffer[j]; //add needed buffer to line
		j++;
	}
}

void	move_buff(char *buffer)
{
	size_t buff_len;
	size_t	line_len;
	size_t	i;

	buff_len = delim_len(buffer, '\0');
	line_len = delim_len(buffer, '\n');
	i = 0;
	if (buffer[line_len] == '\0') // if there's no \n in the buffer
	{
		while (i < BUFFER_SIZE) // fill whole buffer up with \0
		{
			buffer[i] = '\0';
			i++;
		}
		return ;
	}
	while (i <= buff_len - line_len) // if there is a \n, overwrite beginning until \0
	{
		buffer[i] = buffer[line_len + i]; // starting at 0: replace value
		i++;
	}
	buffer[i] = '\0';
}


size_t	delim_len(char	*buffer, char delim) // uitwerken: return? waarom 
{
	size_t	i;

	i = 0;
	if (delim != '\0')
	{
		while (buffer[i] != '\0')
		{
			if (buffer[i] == delim)
				return (i + 1); // +1 because we want the real position 
			i++;
		}
		return (0); // return 0 when no delim found
	}
	while (buffer[i]) //when delim == \0 return length string
		i++;
	return (i); // represents length of the string so no +1
}

char	*line_alloc(size_t length);
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