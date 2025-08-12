/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:47:08 by nicolas           #+#    #+#             */
/*   Updated: 2025/08/12 15:33:29 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_first_line(char *s)
{
	int		line_len;

	line_len = 0;
	while (s[line_len] && s[line_len] != '\n')
		line_len++;
	if (s[line_len] == '\n')
		line_len++;
	return (ft_substr(s, 0, line_len));
}

static ssize_t	read_until_nl(int fd, char **stash)
{
	ssize_t	bytes_read;
	ssize_t	total_bytes_read;
	char	*temp;
	char	*buffer;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	total_bytes_read = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	total_bytes_read += bytes_read;
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = *stash;
		*stash = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		total_bytes_read += bytes_read;
	}
	free(buffer);
	return (total_bytes_read);
}

void	*free_stack(char **stash)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*temp;
	char		*new_line_pos;
	ssize_t		bytes_read;

	if (!stash)
		stash = ft_strdup("");
	new_line_pos = ft_strchr(stash, '\n');
	bytes_read = read_until_nl(fd, &stash);
	if (new_line_pos)
	{
		new_line_pos = ft_strchr(stash, '\n');
		temp = stash;
		stash = ft_strdup(new_line_pos + 1);
		free(temp);
	}
	else if (!new_line_pos && !bytes_read)
		return (free_stack(&stash));
	if (bytes_read == 0 && !ft_strlen(stash))
		return (free_stack(&stash));
	if (bytes_read < 0)
		return (free_stack(&stash));
	return (get_first_line(stash));
}
