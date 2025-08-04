/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:47:08 by nicolas           #+#    #+#             */
/*   Updated: 2025/08/04 17:14:40 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		buf_str[BUFFER_SIZE + 1];
	char		*temp;
	ssize_t		bytes_read;

	bytes_read = read(fd, &buf_str, BUFFER_SIZE);
	if (!line)
		line = ft_strdup("");
	else if(ft_memchr(line, '\n', ft_strlen(line)))
	{
		temp = line;
		line = ft_strdup((char *)ft_memchr(temp, '\n', ft_strlen(temp)) + 1);
		free(temp);
	}
	else if (bytes_read <= 0)
		return (NULL);
	while (bytes_read > 0)
	{
		buf_str[bytes_read] = '\0';
		temp = line;
		line = ft_strjoin(temp, buf_str);
		free(temp);
		if (ft_memchr(buf_str, '\n', BUFFER_SIZE))
			break ;
		bytes_read = read(fd, &buf_str, BUFFER_SIZE);
	}
	return (get_first_line(line));
}
