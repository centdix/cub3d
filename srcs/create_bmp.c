/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:15:41 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/29 13:24:28 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	write_header(int fd, t_all *all)
{
	unsigned int	line_size;

	write(fd, "BM", 2);
	line_size = all->param.screen_w * 3;
	line_size += line_size % 4 ? 4 - line_size % 4 : line_size;
	line_size += 4 - line_size % 4;
	ft_write_int(fd, 54 + line_size * all->param.screen_h);
	ft_write_int(fd, 0);
	ft_write_int(fd, 54);
}

static void	write_info(int fd, t_all *all)
{
	ft_write_int(fd, 40);
	ft_write_int(fd, all->param.screen_w);
	ft_write_int(fd, all->param.screen_h);
	ft_write_half_int(fd, 1);
	ft_write_half_int(fd, 24);
	ft_write_int(fd, 0);
	ft_write_int(fd, 0);
	ft_write_int(fd, 6400);
	ft_write_int(fd, 6400);
	ft_write_int(fd, 0);
	ft_write_int(fd, 0);
}

static void	write_pixel(int fd, t_all *all)
{
	unsigned int	color;
	int				i;
	int				j;
	int				rem;

	rem = all->param.screen_w * 3 % 4;
	i = all->param.screen_h - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < all->param.screen_w)
		{
			color = *(all->image.data_ptr + (all->param.screen_w * i) + j);
			ft_write_color(fd, color);
			j++;
			if (rem)
				ft_write_empty(fd, 4 - rem);
		}
		i--;
	}
}

void		create_bmp(char *file, t_all *all)
{
	int fd;

	if (!(fd = open(file, O_WRONLY | O_CREAT, 0666)))
		return ;
	write_header(fd, all);
	write_info(fd, all);
	write_pixel(fd, all);
	close(fd);
}
