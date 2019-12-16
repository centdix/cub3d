/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 21:18:38 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/28 15:51:33 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_tex(t_param *param, char *line, int id)
{
	if (id == 1)
	{
		while (*line == ' ')
			line++;
		param->path_tex[0] = ft_get_eol(line);
	}
	else if (id == 2)
	{
		while (*line == ' ')
			line++;
		param->path_tex[1] = ft_get_eol(line);
	}
	else if (id == 3)
	{
		while (*line == ' ')
			line++;
		param->path_tex[3] = ft_get_eol(line);
	}
	else if (id == 4)
	{
		while (*line == ' ')
			line++;
		param->path_tex[2] = ft_get_eol(line);
	}
}

static void	handle_line(t_param *param, char *line, int id)
{
	if (id >= 1 && id <= 4)
		line += 3;
	else
		line += 2;
	if (id >= 1 && id <= 4)
		return (get_tex(param, line, id));
	if (id == 0)
	{
		param->screen_w = ft_atoi(line);
		if (param->screen_w > 2560)
			param->screen_w = 2559;
		while (ft_isdigit(*line))
			line++;
		while (*line == ' ')
			line++;
		param->screen_h = ft_atoi(line);
		if (param->screen_h > 1440)
			param->screen_h = 1439;
	}
	else if (id == 5)
		param->path_sp_tex = ft_get_eol(line);
	else if (id == 6 || id == 7)
		return (get_color(param, line, id));
}

static void	dispatcher(t_param *param, char *line)
{
	if (line[0] == 'R')
		return (handle_line(param, line, 0));
	else if (line[0] == 'N' && line[1] == 'O')
		return (handle_line(param, line, 1));
	else if (line[0] == 'S' && line[1] == 'O')
		return (handle_line(param, line, 2));
	else if (line[0] == 'W' && line[1] == 'E')
		return (handle_line(param, line, 3));
	else if (line[0] == 'E' && line[1] == 'A')
		return (handle_line(param, line, 4));
	else if (line[0] == 'S' && line[1] == ' ')
		return (handle_line(param, line, 5));
	else if (line[0] == 'F' && line[1] == ' ')
		return (handle_line(param, line, 6));
	else if (line[0] == 'C' && line[1] == ' ')
		return (handle_line(param, line, 7));
}

static int	handle_file(t_all *all, int fd)
{
	int		ret;
	char	*char_map;
	char	*line;

	ret = 1;
	while (ret > 0)
	{
		if ((ret = get_next_line(fd, &line)) == -1)
			return (-1);
		if (line[0] == '1')
		{
			char_map = parse_map(fd, line);
			get_map(all, char_map);
			free(char_map);
			break ;
		}
		dispatcher(&all->param, line);
		free(line);
	}
	return (ret);
}

int			get_param(t_all *all, char *file)
{
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (-1);
	if ((handle_file(all, fd) == -1))
		return (-1);
	if (!check_file(file))
		return (-1);
	close(fd);
	return (0);
}
