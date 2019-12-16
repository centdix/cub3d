/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 21:19:25 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/28 15:34:29 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*get_value(char *line)
{
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	tmp = ft_substr(line, 0, i);
	result = ft_itoa_base(ft_atoi(tmp), "0123456789abcdef");
	free(tmp);
	if (ft_strlen(result) == 1)
	{
		tmp = result;
		result = ft_strjoin("0", tmp);
		free(tmp);
	}
	return (result);
}

static char	*ft_format(char *r, char *g, char *b)
{
	char	*result;
	char	*tmp;

	tmp = ft_strjoin(r, g);
	result = ft_strjoin(tmp, b);
	free(tmp);
	return (result);
}

int			rgb_to_decimal(char *line)
{
	char	*r;
	char	*g;
	char	*b;
	char	*format;
	int		nb;

	format = NULL;
	r = get_value(line);
	while (ft_isdigit(*line))
		line++;
	while (!ft_isdigit(*line))
		line++;
	g = get_value(line);
	while (ft_isdigit(*line))
		line++;
	while (!ft_isdigit(*line))
		line++;
	b = get_value(line);
	format = ft_format(r, g, b);
	nb = ft_atoi_base(format, "0123456789abcdef");
	free(r);
	free(g);
	free(b);
	free(format);
	return (nb);
}

void		get_color(t_param *param, char *line, int id)
{
	char *tmp;

	if (id == 6)
	{
		while (*line == ' ')
			line++;
		tmp = ft_get_eol(line);
		param->floor_color = rgb_to_decimal(tmp);
		free(tmp);
	}
	else if (id == 7)
	{
		while (*line == ' ')
			line++;
		tmp = ft_get_eol(line);
		param->ceiling_color = rgb_to_decimal(tmp);
		free(tmp);
	}
}

int			ft_isdir(int c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
