/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-koni <bde-koni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:25:40 by bde-koni          #+#    #+#             */
/*   Updated: 2025/01/28 20:24:50 by bde-koni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifdef BUFFER_SIZE
#  include <limits.h>
#  if BUFFER_SIZE > INT_MAX || BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 6
#  endif
# else
#  define BUFFER_SIZE 6
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# include <stddef.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*buff_to_storage(char *buffer);
char	*storage_to_line(char *storage, char *old_line);
size_t	ft_strlen(char *str);
bool	nl_check(char *line);
ssize_t	read_if_buff_empty(int fd, char *buffer, ssize_t bytes_read);
char	*line_alloc(char *storage, char *old_line);
char	*make_line(int fd, char *buffer, ssize_t bytes_read);

#endif