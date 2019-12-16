/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 14:27:16 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/27 14:48:41 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*join_map(char *line, char *current)
{
	char	*char_map;
	char	*tmp;

	char_map = ft_strjoin(current, line);
	tmp = char_map;
	char_map = ft_strjoin(tmp, "\n");
	free(tmp);
	return (char_map);
}

static void	fill_map(int width, int height, char *char_map, t_all *all)
{
	int **map;
	int i;
	int	j;

	if (!(map = malloc(sizeof(int *) * height)))
		return ;
	i = 0;
	while (i < height)
	{
		if (!(map[i] = malloc(sizeof(int) * width)))
			return ;
		j = 0;
		while (j < width)
		{
			if (ft_isdigit(*char_map) || ft_isdir(*char_map))
			{
				map[i][j] = *char_map - '0';
				j++;
			}
			char_map++;
		}
		i++;
	}
	all->param.map = map;
	handle_map(width, height, all);
}

char		*parse_map(int fd, char *line)
{
	char	*char_map;
	char	*tmp;
	int		ret;

	char_map = NULL;
	char_map = join_map(line, char_map);
	free(line);
	ret = 1;
	while (line[0] == '1' && ret > 0)
	{
		ret = get_next_line(fd, &line);
		tmp = char_map;
		char_map = join_map(line, tmp);
		free(tmp);
		free(line);
	}
	return (char_map);
}

void		get_map(t_all *all, char *char_map)
{
	int		width;
	int		height;
	char	*save;

	save = char_map;
	height = 0;
	while (*char_map)
	{
		if (*char_map == '\n' && *(char_map + 1))
			height++;
		char_map++;
	}
	char_map = save;
	width = 0;
	while (*char_map != '\n')
	{
		if (ft_isdigit(*char_map))
			width++;
		char_map++;
	}
	char_map = save;
	all->param.map_width = width;
	all->param.map_height = height;
	return (fill_map(width, height, char_map, all));
}
