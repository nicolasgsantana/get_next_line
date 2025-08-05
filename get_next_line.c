/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:47:08 by nicolas           #+#    #+#             */
/*   Updated: 2025/08/05 16:06:17 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_first_line(const char *s)
{
	char	*line;
	int		line_size;
	int		i;

	line_size = 0;
	while (s[line_size] && s[line_size] != '\n')
		line_size++;
	if (s[line_size] == '\n')
		line_size++;
	line = malloc((line_size + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_size)
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buf_str;
	char		*temp;
	ssize_t		bytes_read;

	buf_str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if(!buf_str)
		return (NULL);
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
	{
		free(buf_str);
		free(line);
		return (NULL);
	}
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
	free(buf_str);
	return (get_first_line(line));
}
