/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:25:40 by bde-koni          #+#    #+#             */
/*   Updated: 2025/01/08 15:26:29 by bde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
char	*update_line(char	*buffer, char	*line, int fd);
char	*buff_to_line(char	*buffer, char	*line);
void	buff_line_join(char *new_line, char *line, char *buffer, size_t buff_add);
void	move_buff(char *buffer);
size_t	delim_len(char	*buffer, char delim);
char	*line_alloc(size_t length);

#endif