/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:35:46 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/25 18:41:18 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	file_handler(char **file, char **line)
{
	int		i;
	int		ret;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (*file[i])
	{
		while ((*file)[i] != '\n' && (*file)[i])
			i++;
		ret = ((*file)[i] == '\n') ? 1 : 0;
		if (!(*line = ft_substr(*file, 0, i)))
			return (-1);
		if (ret == 1)
			if (!(tmp = ft_strdup(*file + i + 1)))
				return (-1);
		free(*file);
		*file = tmp;
		return (ret);
	}
	free(*file);
	*file = NULL;
	if (!(*line = ft_strdup("")))
		return (-1);
	return (0);
}

static int	output(char **file, char **line, int ret)
{
	if (ret == -1)
		return (-1);
	if (ret == 0 && *file == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (file_handler(file, line));
}

int			get_next_line(int fd, char **line)
{
	static char	*file = NULL;
	int			ret;
	char		*tmp;
	char		buf[10 + 1];

	if (fd < 0 || !line || 10 <= 0)
		return (-1);
	while ((ret = read(fd, buf, 10)) > 0)
	{
		buf[ret] = '\0';
		tmp = ft_strjoin(file, buf);
		free(file);
		file = tmp;
		if (ft_strchr(file, '\n'))
			break ;
	}
	return (output(&file, line, ret));
}
