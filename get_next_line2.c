/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:04:17 by bde-koni          #+#    #+#             */
/*   Updated: 2024/12/12 16:38:28 by bde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>

char	*get_next_line(int fd) //check for \n in buffer, extract, shift if necessary, read more data into buffer and '\0' it, return line
{
	ssize_t	buf_size;
	char buffer[buf_size + 1];
	char *line;
	ssize_t	bytes_read;
	char *new_pos;
	
	line = NULL;
	buf_size = 5;
	while (buffer != NULL)
	{
		char *new_pos = ft_strchr(buffer, '\n'); //check for new line and cut off
		if (new_pos != NULL);
		{
			
			append_line(); //extract untill \n
			shift_buffer(); //shift leftovers to the front
			return (line);
		}
		read(fd, buffer, buffer[buf_size]); // read into buffer until we encounter a \0
	}
	append_line(); //extract everything if no \n found
	return (line);
}

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    char *line = NULL;
    ssize_t bytes_read;

    // Process buffer contents
    while (1) {
        // Check for a newline in the current buffer
        char *newline_pos = ft_strchr(buffer, '\n');
        if (newline_pos) {
            // Extract line up to \n
            size_t line_length = newline_pos - buffer + 1;
            line = append_line(line, buffer, line_length);

            // Shift the buffer to remove extracted line
            shift_buffer(buffer, line_length);
            return line;
        }

        // Append entire buffer to the line if no \n is found
        line = append_line(line, buffer, ft_strlen(buffer));
        buffer[0] = '\0'; // Clear buffer

        // Read more data into the buffer
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            // Handle EOF or error
            if (!line || bytes_read < 0) {
                free(line);
                return NULL;
            }
            buffer[0] = '\0'; // No more data
            return line;
        }

        // Null-terminate the buffer
        buffer[bytes_read] = '\0';
    }
}
void	shift_buffer(char *buffer, size_t offset) //shift leftovers to front and '\0' 
{

}

static char	*append_line(char *line, char *buffer, size_t len) //add pieces of line together and return (allocated) line (allocate new length, copy old line part, copy new line part, return new line)
{
	
}
