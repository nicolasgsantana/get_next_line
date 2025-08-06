/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:47:08 by nicolas           #+#    #+#             */
/*   Updated: 2025/08/06 12:28:45 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_first_line(const char *s)
{
	int		line_len;

	line_len = 0;
	while (s[line_len] && s[line_len] != '\n')
		line_len++;
	if (s[line_len] == '\n')
		line_len++;
	return (ft_substr(s, 0, line_len));
}

char	*get_next_line(int fd)
{
	static char	*stack;
	char		*temp;
	char		*buffer;
	char		*new_line;
	ssize_t		bytes_read;
	
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return(NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (!stack)
		stack = ft_strdup("");
	new_line = ft_strchr(stack, '\n');
	if (new_line)
	{
		temp = stack;
		stack = ft_strdup(new_line + 1);
		free(temp);
	}
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = stack;
		stack = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (get_first_line(stack));
}
