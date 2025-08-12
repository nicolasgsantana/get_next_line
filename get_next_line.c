/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:47:08 by nicolas           #+#    #+#             */
/*   Updated: 2025/08/12 11:43:06 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_first_line(char *s)
{
	int		line_len;

	if (!ft_strlen(s))
	{
		free(s);
		return (NULL);
	}
	line_len = 0;
	while (s[line_len] && s[line_len] != '\n')
		line_len++;
	if (s[line_len] == '\n')
		line_len++;
	return (ft_substr(s, 0, line_len));
}

static ssize_t	read_until_nl(int fd, char **stack)
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
		temp = *stack;
		*stack = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		total_bytes_read += bytes_read;
	}
	free(buffer);
	return (total_bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*stack;
	char		*temp;
	char		*new_line_pos;
	ssize_t		bytes_read;

	if (!stack)
		stack = ft_strdup("");
	new_line_pos = ft_strchr(stack, '\n');
	bytes_read = read_until_nl(fd, &stack);
	if (bytes_read <= 0 && !ft_strlen(stack))
		return (NULL);
	if (new_line_pos)
	{
		new_line_pos = ft_strchr(stack, '\n');
		temp = stack;
		stack = ft_strdup(new_line_pos + 1);
		free(temp);
	}
	else if (!new_line_pos && ft_strlen(stack) > 0 && !bytes_read)
	{
		free(stack);
		return (NULL);
	}
	return (get_first_line(stack));
}
