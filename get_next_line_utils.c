/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 10:04:42 by nde-sant          #+#    #+#             */
/*   Updated: 2025/08/04 14:08:25 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc((s1_len + s2_len + 1) * sizeof (char));
	i = 0;
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i - s1_len])
	{
		str[i] = s2[i - s1_len];
		i++;
	}
	str[i] = '\0';
	return (str);
}
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*src;
	unsigned char		to_find;
	size_t				i;

	src = s;
	to_find = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (src[i] == to_find)
			return ((unsigned char *)&src[i]);
		i++;
	}
	return (NULL);
}
char	*ft_strdup(const char *s)
{
	char	*cpy_str;
	int		i;

	cpy_str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!cpy_str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		cpy_str[i] = s[i];
		i++;
	}
	cpy_str[i] = '\0';
	return (cpy_str);
}

char	*get_first_line(const char *s)
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
