/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:47:08 by nicolas           #+#    #+#             */
/*   Updated: 2025/08/04 12:51:50 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		buf_str[BUFFER_SIZE];
	char		*temp;

	if (!line)
		line = malloc(sizeof(char));
	else
	{
		temp = line;
		line = ft_strdup((char *)ft_memchr(temp, '\n', ft_strlen(temp)) + 1);
		free(temp);
	}
	while (read(fd, &buf_str, BUFFER_SIZE) > 0)
	{
		temp = line;
		line = ft_strjoin(temp, buf_str);
		free(temp);
		if (ft_memchr(buf_str, '\n', BUFFER_SIZE))
			break ;
	}
	return (line);
}
