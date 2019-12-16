/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 18:01:47 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/19 15:11:15 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;
	char	*result;

	s1_len = s1 ? ft_strlen(s1) : 0;
	s2_len = s2 ? ft_strlen(s2) : 0;
	if (!(result = malloc(sizeof(char) *
		(s1_len + s2_len + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < s1_len)
	{
		result[i] = s1[i];
		i++;
	}
	while (j < s2_len)
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*result;
	size_t			s_len;

	s_len = s ? ft_strlen(s) : 0;
	if (start >= s_len)
		len = 0;
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			ptr = (char *)&s[i];
			return (ptr);
		}
		i++;
	}
	if (c == '\0')
	{
		ptr = (char *)&s[i];
		return (ptr);
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		i;
	int		len;

	len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
