/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nde-sant <nde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:10:30 by nde-sant          #+#    #+#             */
/*   Updated: 2025/08/13 10:11:15 by nde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	to_find;

	to_find = c;
	i = 0;
	while (s[i] != to_find && s[i] != '\0')
		i++;
	if (s[i] == to_find)
		return ((char *)&s[i]);
	else
		return (0);
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	s_len;
	size_t	new_len;

	s_len = ft_strlen(s);
	if (start > s_len)
		new_len = 0;
	else
		new_len = s_len - start;
	if (len > new_len)
		len = new_len;
	i = 0;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (0);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
