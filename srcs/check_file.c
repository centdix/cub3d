/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:15:05 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/28 15:51:35 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_duplicate(int fd, int *done)
{
	int		ret;
	char	*line;

	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (line[0] == 'R')
			*done += 1;
		if (line[0] == 'N' && line[1] == 'O')
			*done += 1;
		if (line[0] == 'S' && line[1] == 'O')
			*done += 1;
		if (line[0] == 'W' && line[1] == 'E')
			*done += 1;
		if (line[0] == 'E' && line[1] == 'A')
			*done += 1;
		if (line[0] == 'S' && line[1] == ' ')
			*done += 1;
		if (line[0] == 'F' && line[1] == ' ')
			*done += 1;
		if (line[0] == 'C' && line[1] == ' ')
			*done += 1;
	}
	return (ret);
}

int			check_file(char *file)
{
	int len;
	int fd;
	int done;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (0);
	len = ft_strlen(file);
	if (len < 5)
		return (0);
	if (file[len - 1] != 'b' || file[len - 2] != 'u'
		|| file[len - 3] != 'c' || file[len - 4] != '.')
		return (0);
	done = 0;
	if ((check_duplicate(fd, &done) == -1))
		return (0);
	if (done > 8)
		return (0);
	close(fd);
	return (1);
}
