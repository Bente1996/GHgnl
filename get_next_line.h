/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:25:40 by bde-koni          #+#    #+#             */
/*   Updated: 2025/01/21 18:37:39 by bde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# include <stddef.h>
# include <aio.h>

char	*get_next_line(int fd);
char	*buff_to_storage(char *buffer);
char	*storage_to_line(char *storage, char *old_line);
size_t	ft_strlen(char *str);
int		nl_check(char *line);
ssize_t	read_if_buff_empty(int fd, char *buffer, ssize_t bytes_read);
char	*line_alloc(char *storage, char* old_line);
char	*make_line(int fd, char *buffer, ssize_t bytes_read);

#endif